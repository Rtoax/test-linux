#!/bin/bash
set -e
export HPCC_PATH=/opt/hpcc
export HPCC_CLANG_PATH=/opt/hpcc/htgpu_llvm/bin
export HPCC_CLANG=/opt/hpcc/htgpu_llvm
export CUCC_PATH=/opt/hpcc/tools/cu-bridge
export CUDA_PATH=/opt/hpcc/tools/cu-bridge
export CUDA_HOME=/opt/hpcc/tools/cu-bridge
export DEVINFO_ROOT=/opt/hpcc
export LD_LIBRARY_PATH=/opt/hpcc/ompi/lib/:/opt/hpcc/lib:/opt/hpcc/htgpu_llvm/lib:${LD_LIBRARY_PATH}
export PATH=/opt/hpcc/tools/cu-bridge/tools:/opt/hpcc/bin:/opt/hpcc/htgpu_llvm/bin/:${CUCC_PATH}/tools:${CUCC_PATH}/bin:${CUDA_PATH}/bin:$PATH
