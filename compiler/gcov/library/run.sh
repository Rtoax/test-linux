#!/bin/bash

set -e

static=no

CFLAGS_COMMON='-O3 -pthread'
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
		*.log
}

dump_fn1_branch()
{
	local bin=$1
	local fn=$2

	echo -e "\033[1;32m>>> $bin:$fn <<<\033[0m"
	gdb -batch \
		-ex "file $bin" \
		-ex "disassemble $fn" \
		| grep fn1_branch_ \
		| sed 's/^/\t/g'
}

################################################################################
# $1 - libname, for example: libabc.so -> $1 = abc
#      link nothing if empty
compile_test()
{
	local lib=$1

	[[ -e ${testname} ]] && mv $testname $testname.old

	local libarg=${lib:+-L. -l${lib}}

	gcc ${libarg} ${test_srcs} -o $testname ${CFLAGS_COMMON} ${CFLAGS}

	dump_fn1_branch $testname branch_f1
}

compile_test_static()
{
	[[ -e ${testname} ]] && mv $testname $testname.old

	gcc ${libname_a} ${test_srcs} -o $testname ${CFLAGS_COMMON} ${CFLAGS}

	dump_fn1_branch $testname branch_f1
}

compile_lib_dynamic()
{
	[[ -e ${libname_so} ]] && mv ${libname_so}{,.old}

	gcc ${lib_src} -fPIC -shared -o ${libname_so} ${CFLAGS_COMMON} ${CFLAGS}

	compile_test ${libname}

	dump_fn1_branch $libname_so lib_branch_f1
}

compile_lib_static()
{
	[[ -e ${libname_a} ]] && mv ${libname_a}{,.old}

	gcc ${lib_src} -c -o ${lib_src}.o ${CFLAGS_COMMON} ${CFLAGS}
	ar rcs ${libname_a} ${lib_src}.o

	compile_test_static

	dump_fn1_branch $libname_a lib_branch_f1
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
		-gcov_version=1 >/dev/null
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
*)
	cat <<-EOF

	run.sh [-v|--verbose] [-s] [command]

	  -v, --verbose   show verbose
	  -s              compile static library

	  fdo             GCC native static fdo
	  autofdo         AutoFDO

	  clean

	EOF
	;;
esac
