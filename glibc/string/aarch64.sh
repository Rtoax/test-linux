#!/bin/bash

if [[ $(uname -m) == aarch64 ]]; then
	echo "ERROR: You already on aarch64 host"
	exit 1
fi

make clean
make STATIC=1 CROSS_COMPILE=1 "$@"
