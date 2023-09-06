#!/bin/bash

. config

pushd ${TURST_FIRMWARE_A_DIR}
git clean -dfx
make PLAT=qemu DEBUG=1 CROSS_COMPILE=aarch64-linux-gnu- -j8 all
popd
