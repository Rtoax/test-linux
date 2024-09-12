#!/bin/bash

[[ $(uname -m) == aarch64 ]] && echo "ERROR: You already on aarch64, no need to cross compile" && exit 1

make clean
make STATIC=1 ARCH=aarch64 CROSS_COMPILE=aarch64-linux-gnu- SYSROOT=/home/rongtao/rootfs-aarch64 "${@}"

