#!/bin/bash

[[ $(uname -m) ]] && echo "ERROR: You alread on aarch64, no need to cross compile" && exit 1

make ARCH=aarch64 CROSS_COMPILE=aarch64-linux-gnu- SYSROOT=/home/rongtao/rootfs-aarch64

