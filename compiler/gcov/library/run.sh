#!/bin/bash

set -e

compiler=gcc
static=no

CFLAGS_COMMON='-O3 -pthread -DTEST_LIB -DHAVE_INTERFERING_COMPILER'
CFLAGS=

gcov_path=$(pwd)
libname=LIBTEST
libname_so=lib${libname}.so
libname_a=lib${libname}.a
lib_src=library.c

test_srcs=test.c
testname=test

clang_profdata=default.profdata

log_prefix=


clean()
{
	rm -f \
		$testname $testname.old \
		*.so *.so.old \
		*.o *.gcda *.gcno \
		*.gcov \
		*.profraw *.profdata \
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
	elif [[ $static == no ]]; then
		name="Dynamic: $bin:$fn"
	else
		name="$bin:$fn"
	fi

	echo -e "${log_prefix} \033[1;32m>>> Branch: $name <<<\033[0m"
	gdb -batch \
		-ex "file $bin" \
		-ex "disassemble $fn" \
		| grep fn1_branch_ \
		| sed "s|^|${log_prefix}\t|g"
}

dump_layout()
{
	local bin=$1
	local name

	if [[ $static == yes ]]; then
		name="Static: $bin"
	elif [[ $static == no ]]; then
		name="Dynamic: $bin"
	else
		name="$bin:$fn"
	fi

	echo -e "${log_prefix} \033[1;33m>>> Layout: $name <<<\033[0m"

	# Ignore: lib_layout_B_.cold, lib_layout_C.loc[...] in library
	readelf --syms ${bin} | \
		grep "[lib|test]_layout_[A-Z]" | \
		grep -v '.cold' | \
		grep -v '.loc' | \
		grep -v '\[' | \
		grep -v '.constprop' | \
		grep -v gcov | \
		awk '{print $2" "$8}' | \
		sort | \
		uniq | \
		sed "s|^|${log_prefix}\t|g"
}

################################################################################
# $1 - libname, for example: libabc.so -> $1 = abc
#      link nothing if empty
compile_test()
{
	[[ -e ${testname} ]] && mv $testname $testname.old

	${compiler} ${test_srcs} -o $testname ${CFLAGS_COMMON} ${CFLAGS}

	dump_fn1_branch $testname branch_f1
	dump_layout $testname

	if [[ $static == yes ]]; then
		dump_fn1_branch $testname lib_branch_f1
	fi
}

compile_lib_dynamic()
{
	[[ -e ${libname_so} ]] && mv ${libname_so}{,.old}

	${compiler} ${lib_src} -fPIC -shared -o ${libname_so} ${CFLAGS_COMMON} ${CFLAGS}

	CFLAGS+=" -L. -l${libname}"

	compile_test

	dump_fn1_branch $libname_so lib_branch_f1
	dump_layout $libname_so
}

compile_lib_static()
{
	[[ -e ${libname_a} ]] && mv ${libname_a}{,.old}

	${compiler} ${lib_src} -c -o ${lib_src}.o ${CFLAGS_COMMON} ${CFLAGS}
	ar rcs ${libname_a} ${lib_src}.o

	CFLAGS+=" ./${libname_a}"

	compile_test
}

compile_lib()
{
	if [[ $static == no ]]; then
		compile_lib_dynamic
	elif [[ $static == yes ]]; then
		compile_lib_static
	fi
}

################################################################################
# GCC FDO
compile_gen()
{
	case ${compiler} in
	gcc)
	# -O3: has good function layout
	# -O3 -fprofile-generate: For forbidden function layout
	# -O3 -fprofile-use: Good function layout with gcov
	CFLAGS="-fprofile-generate=${gcov_path} -fprofile-arcs -ftest-coverage -lgcov"
	;;
	clang)
	CFLAGS="-fprofile-generate -fprofile-arcs -ftest-coverage -lgcov"
	;;
	esac

	compile_lib
}

compile_use()
{
	case ${compiler} in
	gcc)
	CFLAGS="-fprofile-use=${gcov_path} "
	;;
	clang)
	llvm-profdata merge --output ${clang_profdata} default*.profraw
	CFLAGS="-fprofile-use=${clang_profdata} "
	;;
	esac

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

test_layout()
{
	static=unknown

	log_prefix="-O3                   >>"
	${compiler} test.c -o test -O3 -pthread
	dump_layout test

	log_prefix="-O3+INTERFERING_COMPILER>>"
	${compiler} test.c -o test -O3 -pthread -DHAVE_INTERFERING_COMPILER
	dump_layout test

	log_prefix="-O3+-fprofile-generate>>"
	${compiler} test.c -o test -O3 -pthread -fprofile-generate
	dump_layout test
}

test_test()
{
	case $1 in
	layout)
		shift
		test_layout "$@"
		;;
	*)
		cat <<-EOF

		test [test]

		[test]
		 layout    - test some layout

		EOF
		;;
	esac
}

while :;
do
	case $1 in
	-c|--compiler)
		shift
		compiler=$1
		shift
		if [[ $compiler != gcc ]] && [[ $compiler != clang ]]; then
			echo "ERROR: only support gcc/clang compiler"
			exit 1
		fi
		;;
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
test)
	shift
	test_test "$@"
	;;
fdo)
	clean
	log_prefix="FDO gen>>"
	compile_gen
	log_prefix="FDO run>>"
	run
	log_prefix="FDO opt>>"
	compile_use
	;;
autofdo)
	if [[ ${compiler} != gcc ]]; then
		echo "ERROR: Only gcc support AutoFDO"
		exit 1
	fi
	clean
	log_prefix="AutoFDO record>>"
	af_compile_test
	log_prefix="AutoFDO gcov  >>"
	af_gen_gcov
	log_prefix="AutoFDO optimi>>"
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
	  test [subcommand]
	  dump-test [executable]

	EOF
	;;
esac
