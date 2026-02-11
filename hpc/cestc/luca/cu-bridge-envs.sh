#!/bin/bash

export NV_TOOLS=/usr/local/cuda/
export LUCA_PATH=/opt/luca
export LUCA_CLANG_PATH=/opt/luca/lsgpu_llvm/bin
export CUCC_PATH=/opt/luca/tools/cu-bridge
export PATH=$LUCA_CLANG_PATH:$NV_TOOLS/bin:$CUCC_PATH/tools/:$LUCA_PATH/ompi/bin:$PATH
export LD_LIBRARY_PATH=$LUCA_PATH/ompi/lib:/opt/luca/lib:/opt/luca/lsgpu_llvm/lib:$NV_TOOLS/lib64:$NV_TOOLS/lib64/stubs:$LD_LIBRARY_PATH

echo "Usage: MAKEFLAGS=\"-I/home/rongtao/Git/tst-linux/template/\" make_luca"
