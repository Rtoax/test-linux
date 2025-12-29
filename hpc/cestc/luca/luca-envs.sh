#!/bin/bash
export LUCA_PATH=/opt/luca
export LUCA_CLANG_PATH=/opt/luca/lsgpu_llvm/bin
export LUCA_CLANG=/opt/luca/lsgpu_llvm
export CUCC_PATH=/opt/luca/tools/cu-bridge
export CUDA_PATH=/opt/luca/tools/cu-bridge
export CUDA_HOME=/opt/luca/tools/cu-bridge
export DEVINFO_ROOT=/opt/luca
export LD_LIBRARY_PATH=/opt/luca/ompi/lib/:/opt/luca/lib:/opt/luca/lsgpu_llvm/lib:${LD_LIBRARY_PATH}
export PATH=/opt/luca/tools/cu-bridge/tools:/opt/luca/bin:/opt/luca/lsgpu_llvm/bin/:${CUCC_PATH}/tools:${CUCC_PATH}/bin:${CUDA_PATH}/bin:$PATH
