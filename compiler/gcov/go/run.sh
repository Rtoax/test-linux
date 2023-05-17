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
