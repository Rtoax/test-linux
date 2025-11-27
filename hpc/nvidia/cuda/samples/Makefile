# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include cuda.mk
include rocm.mk
include luca.mk
include hpcc.mk
include compiler.mk

__USE_CUDA_HELPERS__ = ${HAVE_CUDA}
__USE_HIP_HELPERS__ = ${HAVE_HIP}
__USE_LUCA_HELPERS__ = ${HAVE_LUCA}
__USE_HPCC_HELPERS__ = ${HAVE_HPCC}

common-objs := attribute
common-objs += cooperative
common-objs += device
common-objs += dim3
common-objs += event
common-objs += float
common-objs += __GNUC__ __STDC__
common-objs += hello
common-objs += malloc
common-objs += mallocHost
common-objs += mallocManaged
common-objs += memory
common-objs += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
common-objs += module
common-objs += p2p
common-objs += parallel
common-objs += properties

# NVIDIA CUDA
target-nvcc-${HAVE_CUDA} := $(patsubst %,%-nv,$(common-objs))
nvidia-cubin-${HAVE_CUDA} := hello.cu.cubin
nvidia-cubin-${HAVE_CUDA} += parallel.cu.cubin
nvidia-fatbin-${HAVE_CUDA} := hello.cu.fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel.cu.fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel-nv.nv_fatbin
nvidia-fatbin-${HAVE_CUDA} += parallel-nv.nvFatBinSegment
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

# Pure C
target-y := matrix-c-fp32 matrix-c-fp64
target-y += float-c

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
# Remove default so search directory, see ldflags: -Wl,-rpath,/path/to/so/
LDFLAGS_HTCC := -nodefaultrpath

CFLAGS_HTCC_properties := -Wno-string-plus-int

CFLAGS_HTCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_HTCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_HTCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_HTCC_matrix-int8 := -DTEST_INT8=1

CFLAGS_LSCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_LSCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_LSCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_LSCC_matrix-int8 := -DTEST_INT8=1

include main.mk

float-c: ${OUTPUT}float-c.o
matrix-c-fp32: ${OUTPUT}matrix-fp32.o
matrix-c-fp64: ${OUTPUT}matrix-fp64.o

# CUDA
attribute-nv: ${OUTPUT}attribute.cu.o ${CUDA_HELPERS}
cooperative-nv: ${OUTPUT}cooperative.cu.o ${CUDA_HELPERS}
device-nv: ${OUTPUT}device.cu.o ${CUDA_HELPERS}
dim3-nv: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
event-nv: ${OUTPUT}event.cu.o ${CUDA_HELPERS}
float-nv: ${OUTPUT}float.cu.o
__GNUC__-nv: ${OUTPUT}__GNUC__.cu.o
hello-nv: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
malloc-nv: ${OUTPUT}malloc.cu.o ${CUDA_HELPERS}
mallocHost-nv: ${OUTPUT}mallocHost.cu.o ${CUDA_HELPERS}
mallocManaged-nv: ${OUTPUT}mallocManaged.cu.o ${CUDA_HELPERS}
memory-nv: ${OUTPUT}memory.cu.o ${CUDA_HELPERS}
matrix-fp16-nv: ${OUTPUT}matrix-fp16.cu.o ${CUDA_HELPERS}
matrix-fp32-nv: ${OUTPUT}matrix-fp32.cu.o ${CUDA_HELPERS}
matrix-fp64-nv: ${OUTPUT}matrix-fp64.cu.o ${CUDA_HELPERS}
matrix-int8-nv: ${OUTPUT}matrix-int8.cu.o ${CUDA_HELPERS}
module-nv: ${OUTPUT}module.cu.o ${CUDA_HELPERS}
p2p-nv: ${OUTPUT}p2p.cu.o ${CUDA_HELPERS}
parallel-nv: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
properties-nv: ${OUTPUT}properties.cu.o ${CUDA_HELPERS}
__STDC__-nv: ${OUTPUT}__STDC__.cu.o

# ROCm HIP
${OUTPUT}matrix-fp16.hip.o: matrix.cu
${OUTPUT}matrix-fp32.hip.o: matrix.cu
${OUTPUT}matrix-fp64.hip.o: matrix.cu
${OUTPUT}matrix-int8.hip.o: matrix.cu
attribute-hip: ${OUTPUT}attribute.hip.o ${HIP_HELPERS}
cooperative-hip: ${OUTPUT}cooperative.hip.o ${HIP_HELPERS}
device-hip: ${OUTPUT}device.hip.o ${HIP_HELPERS}
dim3-hip: ${OUTPUT}dim3.hip.o ${HIP_HELPERS}
event-hip: ${OUTPUT}event.hip.o ${HIP_HELPERS}
float-hip: ${OUTPUT}float.hip.o ${HIP_HELPERS}
__GNUC__-hip: ${OUTPUT}__GNUC__.hip.o ${HIP_HELPERS}
hello-hip: ${OUTPUT}hello.hip.o ${HIP_HELPERS}
malloc-hip: ${OUTPUT}malloc.hip.o ${HIP_HELPERS}
mallocHost-hip: ${OUTPUT}mallocHost.hip.o ${HIP_HELPERS}
mallocManaged-hip: ${OUTPUT}mallocManaged.hip.o ${HIP_HELPERS}
memory-hip: ${OUTPUT}memory.hip.o ${HIP_HELPERS}
matrix-fp16-hip: ${OUTPUT}matrix-fp16.hip.o ${HIP_HELPERS}
matrix-fp32-hip: ${OUTPUT}matrix-fp32.hip.o ${HIP_HELPERS}
matrix-fp64-hip: ${OUTPUT}matrix-fp64.hip.o ${HIP_HELPERS}
matrix-int8-hip: ${OUTPUT}matrix-int8.hip.o ${HIP_HELPERS}
module-hip: ${OUTPUT}module.hip.o ${HIP_HELPERS}
p2p-hip: ${OUTPUT}p2p.hip.o ${HIP_HELPERS}
parallel-hip: ${OUTPUT}parallel.hip.o ${HIP_HELPERS}
properties-hip: ${OUTPUT}properties.hip.o ${HIP_HELPERS}
__STDC__-hip: ${OUTPUT}__STDC__.hip.o ${HIP_HELPERS}

# HPCC
${OUTPUT}matrix-fp16.hpcc.o: cuda_adapter.h
${OUTPUT}matrix-fp32.hpcc.o: cuda_adapter.h
${OUTPUT}matrix-fp64.hpcc.o: cuda_adapter.h
${OUTPUT}matrix-int8.hpcc.o: cuda_adapter.h
attribute-hpcc: ${OUTPUT}attribute.hpcc.o ${HPCC_HELPERS}
cooperative-hpcc: ${OUTPUT}cooperative.hpcc.o ${HPCC_HELPERS}
device-hpcc: ${OUTPUT}device.hpcc.o ${HPCC_HELPERS}
dim3-hpcc: ${OUTPUT}dim3.hpcc.o ${HPCC_HELPERS}
event-hpcc: ${OUTPUT}event.hpcc.o ${HPCC_HELPERS}
float-hpcc: ${OUTPUT}float.hpcc.o
__GNUC__-hpcc: ${OUTPUT}__GNUC__.hpcc.o ${HPCC_HELPERS}
hello-hpcc: ${OUTPUT}hello.hpcc.o ${HPCC_HELPERS}
malloc-hpcc: ${OUTPUT}malloc.hpcc.o ${HPCC_HELPERS}
mallocHost-hpcc: ${OUTPUT}mallocHost.hpcc.o ${HPCC_HELPERS}
mallocManaged-hpcc: ${OUTPUT}mallocManaged.hpcc.o ${HPCC_HELPERS}
memory-hpcc: ${OUTPUT}memory.hpcc.o ${HPCC_HELPERS}
matrix-fp16-hpcc: ${OUTPUT}matrix-fp16.hpcc.o ${HPCC_HELPERS}
matrix-fp32-hpcc: ${OUTPUT}matrix-fp32.hpcc.o ${HPCC_HELPERS}
matrix-fp64-hpcc: ${OUTPUT}matrix-fp64.hpcc.o ${HPCC_HELPERS}
matrix-int8-hpcc: ${OUTPUT}matrix-int8.hpcc.o ${HPCC_HELPERS}
module-hpcc: ${OUTPUT}module.hpcc.o ${HPCC_HELPERS}
p2p-hpcc: ${OUTPUT}p2p.hpcc.o ${HPCC_HELPERS}
parallel-hpcc: ${OUTPUT}parallel.hpcc.o ${HPCC_HELPERS}
properties-hpcc: ${OUTPUT}properties.hpcc.o ${HPCC_HELPERS}
__STDC__-hpcc: ${OUTPUT}__STDC__.hpcc.o ${HPCC_HELPERS}

# LUCA
${OUTPUT}matrix-fp16.luca.o: cuda_adapter.h
${OUTPUT}matrix-fp32.luca.o: cuda_adapter.h
${OUTPUT}matrix-fp64.luca.o: cuda_adapter.h
${OUTPUT}matrix-int8.luca.o: cuda_adapter.h
attribute-luca: ${OUTPUT}attribute.luca.o ${LUCA_HELPERS}
cooperative-luca: ${OUTPUT}cooperative.luca.o ${LUCA_HELPERS}
device-luca: ${OUTPUT}device.luca.o ${LUCA_HELPERS}
dim3-luca: ${OUTPUT}dim3.luca.o ${LUCA_HELPERS}
event-luca: ${OUTPUT}event.luca.o ${LUCA_HELPERS}
float-luca: ${OUTPUT}float.luca.o
__GNUC__-luca: ${OUTPUT}__GNUC__.luca.o ${LUCA_HELPERS}
hello-luca: ${OUTPUT}hello.luca.o ${LUCA_HELPERS}
malloc-luca: ${OUTPUT}malloc.luca.o ${LUCA_HELPERS}
mallocHost-luca: ${OUTPUT}mallocHost.luca.o ${LUCA_HELPERS}
mallocManaged-luca: ${OUTPUT}mallocManaged.luca.o ${LUCA_HELPERS}
memory-luca: ${OUTPUT}memory.luca.o ${LUCA_HELPERS}
matrix-fp16-luca: ${OUTPUT}matrix-fp16.luca.o ${LUCA_HELPERS}
matrix-fp32-luca: ${OUTPUT}matrix-fp32.luca.o ${LUCA_HELPERS}
matrix-fp64-luca: ${OUTPUT}matrix-fp64.luca.o ${LUCA_HELPERS}
matrix-int8-luca: ${OUTPUT}matrix-int8.luca.o ${LUCA_HELPERS}
module-luca: ${OUTPUT}module.luca.o ${LUCA_HELPERS}
p2p-luca: ${OUTPUT}p2p.luca.o ${LUCA_HELPERS}
parallel-luca: ${OUTPUT}parallel.luca.o ${LUCA_HELPERS}
properties-luca: ${OUTPUT}properties.luca.o ${LUCA_HELPERS}
__STDC__-luca: ${OUTPUT}__STDC__.luca.o ${LUCA_HELPERS}
