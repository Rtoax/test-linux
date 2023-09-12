#!/bin/bash

EDK2_DIR=/home/rongtao/Git/edk2

pushd ${EDK2_DIR}

export EDK_TOOLS_PATH=$PWD/BaseTools

source edksetup.sh

make -C BaseTools

popd
