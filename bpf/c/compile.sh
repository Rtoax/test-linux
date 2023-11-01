#!/bin/bash

__bcc() {
	if [ $# -lt 1 ]; then
		echo $0 [bpf-prog.c]
		return 1
	fi
	local prog=$(realpath $1)
	local arch

	[[ $(uname -m) == aarch64 ]] && arch=arm64
	[[ $(uname -m) == x86_64 ]] && arch=x86-64

	clang -O2 -emit-llvm -c $prog -o - | \
		llc -march=${arch} -filetype=obj -o ${prog%.*}.o
}

__bcc bpf.c
