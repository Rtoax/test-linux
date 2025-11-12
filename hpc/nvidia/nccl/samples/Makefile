# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include ../../cuda/cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk
include ../../../cestc/luca.mk

# NVIDIA CUDA
target-nvcc-${HAVE_NCCL} := ncclGetVersion

# AMD ROCm
rocm-hipcc-${HAVE_RCCL} := hcclGetVersion
target-hipcc-y := $(patsubst %,%-hip,$(rocm-hipcc-y))

# MetaX HPCC
metax-htcc-${HAVE_HPCC} := hcclGetVersion
target-htcc-y := $(patsubst %,%-hpcc,$(metax-htcc-y))

# CESTC LUCA
luca-lscc-${HAVE_LUCA} := hcclGetVersion
target-lscc-y := $(patsubst %,%-luca,$(luca-lscc-y))

include ../../../../template/main.mk

ncclGetVersion: ${OUTPUT}ncclGetVersion.cu.o

# ROCm HIP
ncclGetVersion-hip: ${OUTPUT}ncclGetVersion.hip.o

# MetaX HPCC
hcclGetVersion-hpcc: ${OUTPUT}ncclGetVersion.hpcc.o

# CESTC LUCA
hcclGetVersion-luca: ${OUTPUT}ncclGetVersion.luca.o
