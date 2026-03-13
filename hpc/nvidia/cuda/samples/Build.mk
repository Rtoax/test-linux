# SPDX-License-Identifier: GPL-3.0
include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk
include compiler.mk
include helpers.mk

common-objs += assert
common-objs += attribute
common-objs += cooperative
common-objs += device
common-objs += dim3
common-objs += event
common-objs += float
common-objs += __GNUC__ __STDC__
common-objs += hello
common-objs += graph
common-objs += stream
common-objs += malloc
common-objs += mallocHost
common-objs += mallocManaged
common-objs += memory
common-objs += mempool
common-objs += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
common-objs += module
common-objs += p2p
common-objs += parallel
common-objs += properties
common-objs += rtc
common-objs += version

# NVIDIA CUDA
target-nvcc-${HAVE_CUDA} := $(common-objs)
nvidia-cubin-${HAVE_CUDA} := hello.cu.cubin
nvidia-cubin-${HAVE_CUDA} += parallel.cu.cubin
nvidia-fatbin-${HAVE_CUDA} := hello.cu.fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.cu.fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.nv_fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.nvFatBinSegment
target-post-${HAVE_CUDA} := $(patsubst %,${OUTPUT}%.E.cu,$(common-objs))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.sass.dump,$(common-objs))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.ptx.dump,$(common-objs))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.ptx,$(common-objs))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(common-objs))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%,$(nvidia-cubin-y))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%,$(nvidia-fatbin-y))

# AMD ROCm
target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-objs))
target-post-${HAVE_HIP} += $(patsubst %,${OUTPUT}%-hip.hip_fatbin,$(common-objs))
target-post-${HAVE_HIP} += $(patsubst %,${OUTPUT}%-hip.hipFatBinSegment,$(common-objs))

# HPCC
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%.E.hpcc,$(common-objs))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%.hpcc.devbin,$(common-objs))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%.hpcc.fatbin,$(common-objs))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%-hpcc.hpcc.hc_fatbin,$(common-objs))
target-post-${HAVE_HPCC} += $(patsubst %,${OUTPUT}%-hpcc.hpcc.hcFatBinSegment,$(common-objs))

# LUCA
target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.bitcode,$(common-objs))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.devbin,$(common-objs))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.fatbin,$(common-objs))
target-post-${HAVE_LUCA} += $(patsubst %,${OUTPUT}%.luca.fatbc,$(common-objs))

# Pure C
target-y := matrix-c-fp32 matrix-c-fp64
target-y += float-c

float-c-objs := ${OUTPUT}float-c.o
matrix-c-fp32-objs := ${OUTPUT}matrix-fp32.o
matrix-c-fp64-objs := ${OUTPUT}matrix-fp64.o

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
