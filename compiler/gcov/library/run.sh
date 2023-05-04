#!/bin/bash

set -x

CFLAGS=

compile_test()
{
	gcc -L. -ltest test.c -o test
}

compile_lib()
{
	gcc library.c -fPIC -shared -o libtest.so ${CFLAGS}

	compile_test
}

compile_gen()
{
	CFLAGS="-fprofile-generate=$(pwd) "

	compile_lib
}

compile_use()
{
	CFLAGS="-fprofile-use -fprofile-dir=$(pwd) "

	compile_lib
}

run()
{
	LD_LIBRARY_PATH=. ./test
}

clean()
{
	rm -f test *.so *.o *.gcda
}

case $1 in
compile_gen | compile_use | run | clean)
	cmd=$1
	shift
	$cmd "$@"
	;;
all)
	compile_gen
	run
	compile_use
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
