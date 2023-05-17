#!/bin/bash

unset CGO_CFLAGS
unset CGO_LDFLAGS
go build -o hello hello.go

CFLAGS="-g -O2 -fprofile-generate -fprofile-arcs -ftest-converage -lgcov"
LDFLAGS="-g -O2 -fprofile-arcs -lgcov"
export CGO_CFLAGS=${CFLAGS}
export CGO_LDFLAGS=${LDFLAGS}
go build -o hello1 hello.go

#go build -ldflags="-s" -o hello2 hello.go

autofdo()
{
	local exe=$1
	local perf_data=$exe.perf.data

	perf record -b -e br_inst_retired.near_taken:pp -o $perf_data -- ./$exe
	create_gcov --binary=$exe --profile=$perf_data --gcov=$exe.gcov -gcov_version=1
	dump_gcov $exe.gcov
}

autofdo hello
autofdo hello1
