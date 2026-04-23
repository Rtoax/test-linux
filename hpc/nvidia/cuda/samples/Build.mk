# SPDX-License-Identifier: GPL-3.0
include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk
include compiler.mk
include helpers.mk

common-exe += assert
common-exe += attribute
common-exe += cooperative
common-exe += device
common-exe += dim3
common-exe += event
common-exe += float
common-exe += __GNUC__ __STDC__
common-exe += hello
common-exe += graph
common-exe += stream
common-exe += malloc
common-exe += mallocHost
common-exe += mallocManaged
common-exe += memory
common-exe += mempool
common-exe += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
common-exe += module
common-exe += oom
common-exe += p2p
common-exe += parallel
common-exe += properties
common-exe += rtc
common-exe += version

# NVIDIA CUDA
target-nvcc-${HAVE_CUDA} := $(common-exe)
nvidia-cubin-${HAVE_CUDA} := hello.cu.cubin
nvidia-cubin-${HAVE_CUDA} += parallel.cu.cubin
nvidia-fatbin-${HAVE_CUDA} := hello.cu.fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.cu.fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.nv_fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.nvFatBinSegment
target-post-${HAVE_CUDA} := $(patsubst %,${OUTPUT}%.E.cu,$(common-exe))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.sass.dump,$(common-exe))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.ptx.dump,$(common-exe))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.ptx,$(common-exe))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(common-exe))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%,$(nvidia-cubin-y))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%,$(nvidia-fatbin-y))

# AMD ROCm
target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-exe))
target-post-${HAVE_HIP} += $(patsubst %,${OUTPUT}%-hip.hip_fatbin,$(common-exe))
target-post-${HAVE_HIP} += $(patsubst %,${OUTPUT}%-hip.hipFatBinSegment,$(common-exe))

# HPCC
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-exe))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%.E.hpcc,$(common-exe))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%.hpcc.devbin,$(common-exe))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%.hpcc.fatbin,$(common-exe))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%-hpcc.hpcc.hc_fatbin,$(common-exe))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%-hpcc.hpcc.hcFatBinSegment,$(common-exe))

# LUCA
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-exe))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.bitcode,$(common-exe))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.devbin,$(common-exe))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.fatbin,$(common-exe))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.fatbc,$(common-exe))

# Pure C
target-y := matrix-c-fp32 matrix-c-fp64
target-y += float-c

float-c-objs := float-c.o
matrix-c-fp32-objs := matrix-fp32.o
matrix-c-fp64-objs := matrix-fp64.o

CFLAGS += -I..
CFLAGS_matrix-fp64 := -DTEST_FP64=1
CFLAGS_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_NVCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1
# NOTE: warning: ‘CUresult cuDeviceComputeCapability(int*, int*, CUdevice)’ is deprecated [-Wdeprecated-declarations]
CFLAGS_NVCC_properties := -Wno-deprecated-declarations

CFLAGS_float-c := ${cflags-support-types-y}
LDFLAGS_float-c := -lm

# FIXME: on my fedora 42 env:
# fatal error: 'bits/c++config.h' file not found
CFLAGS_HIPCC := -I/usr/include/c++/15/x86_64-redhat-linux/
CFLAGS_HIPCC += -I.
CFLAGS_HIPCC += -Wno-unused-result

CFLAGS_HIPCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_HIPCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_HIPCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_HIPCC_matrix-int8 := -DTEST_INT8=1

CFLAGS_HTCC := -Wno-c99-designator

CFLAGS_HTCC_properties := -Wno-string-plus-int

CFLAGS_HTCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_HTCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_HTCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_HTCC_matrix-int8 := -DTEST_INT8=1

CFLAGS_LSCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_LSCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_LSCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_LSCC_matrix-int8 := -DTEST_INT8=1
