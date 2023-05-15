#!/bin/bash

set -e

CFLAGS_COMMON='-O3 -pthread'
CFLAGS=

gcov_path=$(pwd)
libname=LIBTEST
libname_so=lib${libname}.so

clean()
{
	rm -f \
		test test.old \
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
	[[ -e test ]] && mv test test.old
	gcc -L. -l${libname} test.c -o test ${CFLAGS_COMMON} ${CFLAGS}
}

compile_lib()
{
	gcc library.c -fPIC -shared -o ${libname_so} ${CFLAGS_COMMON} ${CFLAGS}

	compile_test

	dump_fn1_branch $libname_so lib_branch_f1
	dump_fn1_branch test branch_f1
}

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

run()
{
	LD_LIBRARY_PATH=. ./test
}
run_gen()
{
	LD_LIBRARY_PATH=. ./test.old
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
fdo-all)
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

	  fdo-all       - all above

	EOF
	;;
esac
