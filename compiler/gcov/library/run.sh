#!/bin/bash

set -e

static=no

CFLAGS_COMMON='-O3 -pthread -DTEST_LIB'
CFLAGS=

gcov_path=$(pwd)
libname=LIBTEST
libname_so=lib${libname}.so
libname_a=lib${libname}.a
lib_src=library.c

test_srcs=test.c
testname=test


clean()
{
	rm -f \
		$testname $testname.old \
		*.so *.so.old \
		*.o *.gcda *.gcno \
		*.gcov \
		perf.data* \
		*.log \
		*.a *.a.old \
		*.out
}

dump_fn1_branch()
{
	local bin=$1
	local fn=$2
	local name

	if [[ $static == yes ]]; then
		name="Static: $bin:$fn"
	else
		name="Dynamic: $bin:$fn"
	fi

	echo -e "\033[1;32m>>> Branch: $name <<<\033[0m"
	gdb -batch \
		-ex "file $bin" \
		-ex "disassemble $fn" \
		| grep fn1_branch_ \
		| sed 's/^/\t/g'
}

dump_layout()
{
	local bin=$1
	local name

	if [[ $static == yes ]]; then
		name="Static: $bin"
	else
		name="Dynamic: $bin"
	fi

	echo -e "\033[1;33m>>> Layout: $name <<<\033[0m"
	readelf --syms ${bin} | \
		grep "[lib|test]_layout_[A-Z]" | \
		grep -v gcov | \
		awk '{print $2" "$8}' | \
		sort | \
		uniq | \
		sed 's/^/\t/g'
}

################################################################################
# $1 - libname, for example: libabc.so -> $1 = abc
#      link nothing if empty
compile_test()
{
	[[ -e ${testname} ]] && mv $testname $testname.old

	gcc ${test_srcs} -o $testname ${CFLAGS_COMMON} ${CFLAGS}

	dump_fn1_branch $testname branch_f1
	dump_layout $testname

	if [[ $static == yes ]]; then
		dump_fn1_branch $testname lib_branch_f1
	fi
}

compile_lib_dynamic()
{
	[[ -e ${libname_so} ]] && mv ${libname_so}{,.old}

	gcc ${lib_src} -fPIC -shared -o ${libname_so} ${CFLAGS_COMMON} ${CFLAGS}

	CFLAGS+=" -L. -l${libname}"

	compile_test

	dump_fn1_branch $libname_so lib_branch_f1
	dump_layout $libname_so
}

compile_lib_static()
{
	[[ -e ${libname_a} ]] && mv ${libname_a}{,.old}

	gcc ${lib_src} -c -o ${lib_src}.o ${CFLAGS_COMMON} ${CFLAGS}
	ar rcs ${libname_a} ${lib_src}.o

	CFLAGS+=" ./${libname_a}"

	compile_test
}

compile_lib()
{
	if [[ $static == no ]]; then
		compile_lib_dynamic
	else
		compile_lib_static
	fi
}

################################################################################
# GCC FDO
compile_gen()
{
	CFLAGS="-fprofile-generate=${gcov_path} -fprofile-arcs -ftest-coverage -lgcov"

	compile_lib
}

compile_use()
{
	CFLAGS="-fprofile-use=${gcov_path} "

	compile_lib
}

################################################################################
# GCC AutoFDO
#  LD_LIBRARY_PATH=. perf record -b -e br_inst_retired.near_taken:pp -- ./test
#  create_gcov --binary=test --profile=perf.data --gcov=test-autofdo.gcov -gcov_version=1
#  dump_gcov test-autofdo.gcov
af_test_gcov=$testname-autofdo.gcov
af_compile_test()
{
	# AutoFDO profile is represented using debug info
	CFLAGS='-g'

	compile_lib
}

af_gen_gcov()
{
	LD_LIBRARY_PATH=. \
		perf record -b -e br_inst_retired.near_taken:pp -- ./$testname

	create_gcov \
		--binary=$testname \
		--profile=perf.data \
		--gcov=$af_test_gcov \
		-gcov_version=1 \
		2>/dev/null 1>/dev/null
}

# FIXME: WHY? AutoFDO doesn't works for dynamic library
af_compile_test_2nd()
{
	CFLAGS="-fauto-profile=${af_test_gcov}"

	compile_lib
}


run()
{
	LD_LIBRARY_PATH=. ./$testname
}
run_gen()
{
	LD_LIBRARY_PATH=. ./$testname.old
}

while :;
do
	case $1 in
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	-s)
		shift
		static=yes
		;;
	*)
		break
		;;
	esac
done

case $1 in
compile_gen | compile_use | run | run_gen | clean)
	cmd=$1
	shift
	$cmd "$@"
	;;
fdo)
	clean
	compile_gen
	run
	compile_use
	;;
autofdo)
	af_compile_test
	af_gen_gcov
	af_compile_test_2nd
	;;
dump-test)
	shift
	dump_fn1_branch $1 branch_f1
	dump_layout $1
	;;
*)
	cat <<-EOF

	run.sh [-v|--verbose] [-s] [command]

	  -v, --verbose   show verbose
	  -s              compile static library

	  fdo             GCC native static fdo
	  autofdo         AutoFDO

	  clean
	  dump-test [executable]

	EOF
	;;
esac
