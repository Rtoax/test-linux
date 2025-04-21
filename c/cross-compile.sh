#!/bin/bash

case $(basename $0) in
aarch64.sh) ARCH=aarch64 ;;
x86_64.sh) ARCH=x86_64 ;;
*) echo >&2 "ERROR: not support arch" && exit 1 ;;
esac

[[ $(uname -m) == ${ARCH} ]] && echo >&2 "ERROR: You already on ${ARCH}, no need to cross compile" && exit 1

make clean
make STATIC=1 ARCH=${ARCH} CROSS_COMPILE=${ARCH}-linux-gnu- SYSROOT=/home/rongtao/rootfs-${ARCH} "${@}"

