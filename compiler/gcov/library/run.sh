#!/bin/bash

set -e

CFLAGS_COMMON='-O3 -pthread'
CFLAGS=

gcov_path=$(pwd)
libname=LIBTEST
libname_so=lib${libname}.so
lib_srcs=library.c

test_srcs=test.c
testname=test


clean()
{
	rm -f \
		$testname $testname.old \
		*.so *.o *.gcda *.gcno \
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

compile_test()
{
	[[ -e test ]] && mv $testname $testname.old
	gcc -L. -l${libname} ${test_srcs} -o $testname ${CFLAGS_COMMON} ${CFLAGS}
}

compile_lib()
{
	gcc ${lib_srcs} -fPIC -shared -o ${libname_so} ${CFLAGS_COMMON} ${CFLAGS}

	compile_test

	dump_fn1_branch $libname_so lib_branch_f1
	dump_fn1_branch $testname branch_f1
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
# TODO: GCC AutoFDO


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
		set -x
		;;
	-vv)
		shift
		export PS4='+${BASH_SOURCE}: '
		set -x
		;;
	-vvv)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}: '
		set -x
		;;
	-vvvv)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
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
*)
	cat <<-EOF

	GCC -fprofile-generate:

	  compile_gen
	  run
	  run_gen
	  compile_use
	  clean

	  fdo          - all above

	EOF
	;;
esac
