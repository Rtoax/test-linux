#!/bin/bash

export CGO_CFLAGS="-g -O2 -fprofile-generate -fprofile-arcs -ftest-converage -lgcov"
export CGO_LDFLAGS="-g -O2 -fprofile-arcs -lgcov"
go build hello.go
./hello
