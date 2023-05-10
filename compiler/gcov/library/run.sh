#!/bin/bash

set -e

CFLAGS_COMMON='-O3 -pthread'
CFLAGS=

gcov_path=$(pwd)


clean()
{
	rm -f test *.so *.o *.gcda
}

compile_test()
{
	gcc -L. -ltest test.c -o test ${CFLAGS_COMMON} ${CFLAGS}
}

compile_lib()
{
	gcc library.c -fPIC -shared -o libtest.so ${CFLAGS_COMMON} ${CFLAGS}

	compile_test
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

case $1 in
compile_gen | compile_use | run | clean)
	cmd=$1
	shift
	$cmd "$@"
	;;
all)
	clean
	compile_gen
	dump_fn1_branch libtest.so lib_branch_f1
	dump_fn1_branch test branch_f1
	run
	compile_use
	dump_fn1_branch libtest.so lib_branch_f1
	dump_fn1_branch test branch_f1
	;;
*)
	cat <<-EOF

	compile_gen
	run
	compile_use
	clean

	all

	EOF
	;;
esac
