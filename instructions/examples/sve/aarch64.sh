#!/bin/bash

SYSROOT=/home/rongtao/rootfs-aarch64

if [[ $(uname -m) == aarch64 ]]; then
	echo "ERROR: You already on aarch64 host"
	exit 1
fi

if [[ ! -d ${SYSROOT} ]]; then
	echo "ERROR: ${SYSROOT} is not exist."
	exit 1
fi

make clean
make STATIC=1 CROSS_COMPILE=1 SYSROOT=${SYSROOT} "$@"
