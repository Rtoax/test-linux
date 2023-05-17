#!/bin/bash

hello_go()
{
	local CFLAGS LDFLAGS

	unset CGO_CFLAGS
	unset CGO_LDFLAGS
	go build -o hello hello.go

	CFLAGS="-g -O2 -fprofile-generate -fprofile-arcs -ftest-coverage -lgcov"
	LDFLAGS="-g -O2 -fprofile-arcs -lgcov"
	unset CGO_CFLAGS
	unset CGO_LDFLAGS
	export CGO_CFLAGS=${CFLAGS}
	export CGO_LDFLAGS=${LDFLAGS}
	go build -o hello1 hello.go

	#
	CFLAGS="-g -O2"
	LDFLAGS="-g -O2"
	unset CGO_CFLAGS
	unset CGO_LDFLAGS
	export CGO_CFLAGS=${CFLAGS}
	export CGO_LDFLAGS=${LDFLAGS}
	go build -o hello2 hello.go

	#go build -ldflags="-s" -o hello2 hello.go
}

hello_c()
{
	local CFLAGS=-O0

	gcc hello.c ${CFLAGS} -o hello
	gcc hello.c -g ${CFLAGS} -fprofile-generate -fprofile-arcs -ftest-coverage -lgcov -o hello1
	gcc hello.c -g ${CFLAGS} -o hello2
}

autofdo()
{
	local exe=$1
	local perf_data=$exe.perf.data

	perf record -b -e br_inst_retired.near_taken:pp -o $perf_data -- ./$exe /etc/os-release
	create_gcov --binary=$exe --profile=$perf_data --gcov=$exe.gcov -gcov_version=1

	echo "============= Dump GCOV Start =============="
	dump_gcov $exe.gcov | sed 's/^/\t/g'
	echo "============= Dump GCOV End =============="
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

