#!/bin/bash

hello_go()
{
	local CFLAGS LDFLAGS

	print_go_env() {
		echo "============ Go ENV ============="
		go env CGO_CFLAGS | sed 's/^/ CGO_CFLAGS=/g'
		go env CGO_LDFLAGS | sed 's/^/ CGO_LDFLAGS=/g'
	}

	unset CGO_CFLAGS
	unset CGO_LDFLAGS
	print_go_env
	go build -o hello hello.go

	CFLAGS="-g -O2 -fprofile-generate -fprofile-arcs -ftest-coverage -lgcov"
	LDFLAGS="-g -O2 -fprofile-arcs -lgcov"
	unset CGO_CFLAGS
	unset CGO_LDFLAGS
	export CGO_CFLAGS=${CFLAGS}
	export CGO_LDFLAGS=${LDFLAGS}
	print_go_env
	go build -o hello1 hello.go

	# man gcc
	CFLAGS="-gz=none -O2"
	LDFLAGS="-gz=none -O2"
	unset CGO_CFLAGS
	unset CGO_LDFLAGS
	export CGO_CFLAGS=${CFLAGS}
	export CGO_LDFLAGS=${LDFLAGS}
	print_go_env
	go build -o hello2 hello.go

	#go build -ldflags="-s" -o hello2 hello.go
}

hello_c()
{
	local CFLAGS=-O0

	gcc hello.c ${CFLAGS} -o hello
	gcc hello.c -g ${CFLAGS} -fprofile-generate -fprofile-arcs -ftest-coverage -lgcov -o hello1
	gcc hello.c -g ${CFLAGS} -o hello2
	gcc hello.c -g -gz=zlib-gnu ${CFLAGS} -o hello3
}

autofdo()
{
	local exe=$1
	local perf_data=$exe.perf.data

	echo -e '\033[33m'
	perf record -b -e br_inst_retired.near_taken:pp -o $perf_data -- ./$exe /etc/os-release
	echo -e '\033[m'

	echo -e '\033[34m'
	create_gcov --binary=$exe --profile=$perf_data --gcov=$exe.gcov -gcov_version=1
	echo -e '\033[m'

	echo -e '\033[32m'
	echo "============= Dump GCOV Start =============="
	dump_gcov $exe.gcov | sed 's/^/\t/g'
	echo "============= Dump GCOV End =============="
	echo -e '\033[m'
}

case $1 in
go)
	hello_go
	;;
c)
	hello_c
	;;
*)
	cat <<-EOF
	run.sh [go|c]
	EOF
	exit 1
	;;
esac

autofdo hello
autofdo hello1
autofdo hello2

