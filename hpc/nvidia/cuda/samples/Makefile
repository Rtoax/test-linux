# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include ../../../../compiler/compiler.mk
include ../cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk
include ../../../cestc/luca.mk

common-objs := attribute
common-objs += blas
common-objs += blasLtMatmul
common-objs += cooperative
common-objs += device
common-objs += dim3
common-objs += event
common-objs += fft
common-objs += float
common-objs += __GNUC__ __STDC__
common-objs += hello
common-objs += malloc
common-objs += mallocManaged
common-objs += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
common-objs += module
common-objs += p2p
common-objs += parallel
common-objs += properties
common-objs += rand
common-objs += sparse

ifdef HAVE_CUDA
  target-nvcc-y := ${common-objs}

  # NCCL
  ifdef HAVE_NCCL
    target-nvcc-y += ncclGetVersion
  endif

  obj-cubin := hello.cubin
  obj-cubin += parallel.cubin
  obj-fatbin := hello.fatbin
  obj-fatbin += parallel.fatbin parallel.nv_fatbin parallel.nvFatBinSegment
endif

ifdef HAVE_HIP
  rocm-hipcc := ${common-objs}

  # RCCL
  ifdef HAVE_RCCL
    rocm-hipcc += ncclGetVersion
  endif

  rocm-fatbin := parallel.hip_fatbin parallel.hipFatBinSegment

  target-hipcc-y := $(patsubst %,%-hip,$(rocm-hipcc))
endif

ifdef HAVE_HPCC
  metax-htcc := ${common-objs}

  # HCCL
  metax-htcc += hcclGetVersion

  metax-devbin := hello.hpcc.devbin
  metax-devbin += parallel.hpcc.devbin
  metax-fatbin := hello.hpcc.fatbin
  metax-fatbin += parallel.hpcc.fatbin
  metax-fatbin += parallel-hpcc.hpcc.hc_fatbin
  metax-fatbin += parallel-hpcc.hpcc.hcFatBinSegment

  target-htcc-y := $(patsubst %,%-hpcc,$(metax-htcc))
endif

ifdef HAVE_LUCA
  target-lscc-y := hello-luca
  target-lscc-y += __GNUC__-luca
  target-lscc-y += __STDC__-luca
endif

target-post-y := $(patsubst %,${OUTPUT}%.E.cu,$(target-nvcc-y))
target-post-y += $(patsubst %,${OUTPUT}%.cu.sass.dump,$(target-nvcc-y))
target-post-y += $(patsubst %,${OUTPUT}%.cu.ptx.dump,$(target-nvcc-y))
target-post-y += $(patsubst %,${OUTPUT}%.ptx,$(target-nvcc-y))
target-post-y += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(target-nvcc-y))
target-post-y += $(patsubst %,${OUTPUT}%,$(obj-cubin))
target-post-y += $(patsubst %,${OUTPUT}%,$(obj-fatbin))
# ROCm HIP
target-post-y += $(patsubst %,${OUTPUT}%,$(rocm-fatbin))
# MetaX
target-post-y += $(patsubst %,${OUTPUT}%.E.hpcc,$(metax-htcc))
target-post-y += $(patsubst %,${OUTPUT}%,$(metax-devbin))
target-post-y += $(patsubst %,${OUTPUT}%,$(metax-fatbin))

# Pure C
target-y := matrix-c-fp32 matrix-c-fp64
target-y += float-c

CFLAGS_matrix-fp64 := -DTEST_FP64=1
CFLAGS_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_NVCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1
# NOTE: warning: ‘CUresult cuDeviceComputeCapability(int*, int*, CUdevice)’ is deprecated [-Wdeprecated-declarations]
CFLAGS_NVCC_properties := -Wno-deprecated-declarations

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o
HIP_HELPERS := ${OUTPUT}cuda_helpers.hip.o
HPCC_HELPERS := ${OUTPUT}cuda_helpers.hpcc.o
LUCA_HELPERS := ${OUTPUT}cuda_helpers.luca.o

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
CFLAGS_HTCC_blasLtMatmul := ${CFLAGS_HTCC_blas}

CFLAGS_HTCC_blas := -Wno-ignored-attributes
CFLAGS_HTCC_blasLtMatmul := ${CFLAGS_HTCC_blas}

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h
${HIP_HELPERS}: cuda_helpers.h
${HPCC_HELPERS}: cuda_helpers.h

# CUDA
attribute: ${OUTPUT}attribute.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
blasLtMatmul: ${OUTPUT}blasLtMatmul.cu.o ${CUDA_HELPERS}
cooperative: ${OUTPUT}cooperative.cu.o ${CUDA_HELPERS}
device: ${OUTPUT}device.cu.o ${CUDA_HELPERS}
dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
event: ${OUTPUT}event.cu.o ${CUDA_HELPERS}
fft: ${OUTPUT}fft.cu.o ${CUDA_HELPERS}
float: ${OUTPUT}float.cu.o
float-c: ${OUTPUT}float-c.o
__GNUC__: ${OUTPUT}__GNUC__.cu.o
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
malloc: ${OUTPUT}malloc.cu.o ${CUDA_HELPERS}
mallocManaged: ${OUTPUT}mallocManaged.cu.o ${CUDA_HELPERS}
matrix-c-fp32: ${OUTPUT}matrix-fp32.o
matrix-c-fp64: ${OUTPUT}matrix-fp64.o
matrix-fp16: ${OUTPUT}matrix-fp16.cu.o ${CUDA_HELPERS}
matrix-fp32: ${OUTPUT}matrix-fp32.cu.o ${CUDA_HELPERS}
matrix-fp64: ${OUTPUT}matrix-fp64.cu.o ${CUDA_HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.cu.o ${CUDA_HELPERS}
module: ${OUTPUT}module.cu.o ${CUDA_HELPERS}
ncclGetVersion: ${OUTPUT}ncclGetVersion.cu.o ${CUDA_HELPERS}
p2p: ${OUTPUT}p2p.cu.o ${CUDA_HELPERS}
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
properties: ${OUTPUT}properties.cu.o ${CUDA_HELPERS}
rand: ${OUTPUT}rand.cu.o ${CUDA_HELPERS}
sparse: ${OUTPUT}sparse.cu.o ${CUDA_HELPERS}
__STDC__: ${OUTPUT}__STDC__.cu.o

# ROCm HIP
${OUTPUT}attribute.hip.o: attribute.cu
${OUTPUT}blas.hip.o: blas.cu
${OUTPUT}blasLtMatmul.hip.o: blasLtMatmul.cu
${OUTPUT}cooperative.hip.o: cooperative.cu
${OUTPUT}device.hip.o: device.cu
${OUTPUT}dim3.hip.o: dim3.cu
${OUTPUT}event.hip.o: event.cu
${OUTPUT}fft.hip.o: fft.cu
${OUTPUT}float.hip.o: float.cu
${OUTPUT}hello.hip.o: hello.cu
${OUTPUT}malloc.hip.o: malloc.cu
${OUTPUT}mallocManaged.hip.o: mallocManaged.cu
${OUTPUT}matrix-fp16.hip.o: matrix.cu
${OUTPUT}matrix-fp32.hip.o: matrix.cu
${OUTPUT}matrix-fp64.hip.o: matrix.cu
${OUTPUT}matrix-int8.hip.o: matrix.cu
${OUTPUT}module.hip.o: module.cu
${OUTPUT}ncclGetVersion.hip.o: ncclGetVersion.cu
${OUTPUT}p2p.hip.o: p2p.cu
${OUTPUT}parallel.hip.o: parallel.cu
${OUTPUT}properties.hip.o: matrix.cu
${OUTPUT}rand.hip.o: rand.cu
${OUTPUT}sparse.hip.o: sparse.cu
attribute-hip: ${OUTPUT}attribute.hip.o ${HIP_HELPERS}
blas-hip: ${OUTPUT}blas.hip.o ${HIP_HELPERS}
blasLtMatmul-hip: ${OUTPUT}blasLtMatmul.hip.o ${HIP_HELPERS}
cooperative-hip: ${OUTPUT}cooperative.hip.o ${HIP_HELPERS}
device-hip: ${OUTPUT}device.hip.o ${HIP_HELPERS}
dim3-hip: ${OUTPUT}dim3.hip.o ${HIP_HELPERS}
event-hip: ${OUTPUT}event.hip.o ${HIP_HELPERS}
fft-hip: ${OUTPUT}fft.hip.o ${HIP_HELPERS}
float-hip: ${OUTPUT}float.hip.o ${HIP_HELPERS}
__GNUC__-hip: ${OUTPUT}__GNUC__.hip.o ${HIP_HELPERS}
hello-hip: ${OUTPUT}hello.hip.o ${HIP_HELPERS}
malloc-hip: ${OUTPUT}malloc.hip.o ${HIP_HELPERS}
mallocManaged-hip: ${OUTPUT}mallocManaged.hip.o ${HIP_HELPERS}
matrix-fp16-hip: ${OUTPUT}matrix-fp16.hip.o ${HIP_HELPERS}
matrix-fp32-hip: ${OUTPUT}matrix-fp32.hip.o ${HIP_HELPERS}
matrix-fp64-hip: ${OUTPUT}matrix-fp64.hip.o ${HIP_HELPERS}
matrix-int8-hip: ${OUTPUT}matrix-int8.hip.o ${HIP_HELPERS}
module-hip: ${OUTPUT}module.hip.o ${HIP_HELPERS}
ncclGetVersion-hip: ${OUTPUT}ncclGetVersion.hip.o
p2p-hip: ${OUTPUT}p2p.hip.o ${HIP_HELPERS}
parallel-hip: ${OUTPUT}parallel.hip.o ${HIP_HELPERS}
properties-hip: ${OUTPUT}properties.hip.o ${HIP_HELPERS}
rand-hip: ${OUTPUT}rand.hip.o ${HIP_HELPERS}
sparse-hip: ${OUTPUT}sparse.hip.o ${HIP_HELPERS}
__STDC__-hip: ${OUTPUT}__STDC__.hip.o ${HIP_HELPERS}

# MetaX HPCC
${OUTPUT}blas.hpcc.o: blas.cu
${OUTPUT}blasLtMatmul.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}device.hpcc.o: device.cu
${OUTPUT}fft.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}float.hpcc.o: float.cu
${OUTPUT}hcclGetVersion.hpcc.o: ncclGetVersion.cu
${OUTPUT}matrix-fp16.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-fp32.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-fp64.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-int8.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}rand.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}sparse.hpcc.o: cuda_adapter.h cuda_helpers.h
attribute-hpcc: ${OUTPUT}attribute.hpcc.o ${HPCC_HELPERS}
blas-hpcc: ${OUTPUT}blas.hpcc.o ${HPCC_HELPERS}
blasLtMatmul-hpcc: ${OUTPUT}blasLtMatmul.hpcc.o ${HPCC_HELPERS}
cooperative-hpcc: ${OUTPUT}cooperative.hpcc.o ${HPCC_HELPERS}
device-hpcc: ${OUTPUT}device.hpcc.o ${HPCC_HELPERS}
dim3-hpcc: ${OUTPUT}dim3.hpcc.o ${HPCC_HELPERS}
event-hpcc: ${OUTPUT}event.hpcc.o ${HPCC_HELPERS}
fft-hpcc: ${OUTPUT}fft.hpcc.o ${HPCC_HELPERS}
float-hpcc: ${OUTPUT}float.hpcc.o
__GNUC__-hpcc: ${OUTPUT}__GNUC__.hpcc.o ${HPCC_HELPERS}
hcclGetVersion-hpcc: ${OUTPUT}hcclGetVersion.hpcc.o ${HPCC_HELPERS}
hello-hpcc: ${OUTPUT}hello.hpcc.o ${HPCC_HELPERS}
malloc-hpcc: ${OUTPUT}malloc.hpcc.o ${HPCC_HELPERS}
mallocManaged-hpcc: ${OUTPUT}mallocManaged.hpcc.o ${HPCC_HELPERS}
matrix-fp16-hpcc: ${OUTPUT}matrix-fp16.hpcc.o ${HPCC_HELPERS}
matrix-fp32-hpcc: ${OUTPUT}matrix-fp32.hpcc.o ${HPCC_HELPERS}
matrix-fp64-hpcc: ${OUTPUT}matrix-fp64.hpcc.o ${HPCC_HELPERS}
matrix-int8-hpcc: ${OUTPUT}matrix-int8.hpcc.o ${HPCC_HELPERS}
module-hpcc: ${OUTPUT}module.hpcc.o ${HPCC_HELPERS}
p2p-hpcc: ${OUTPUT}p2p.hpcc.o ${HPCC_HELPERS}
parallel-hpcc: ${OUTPUT}parallel.hpcc.o ${HPCC_HELPERS}
properties-hpcc: ${OUTPUT}properties.hpcc.o ${HPCC_HELPERS}
rand-hpcc: ${OUTPUT}rand.hpcc.o ${HPCC_HELPERS}
sparse-hpcc: ${OUTPUT}sparse.hpcc.o ${HPCC_HELPERS}
__STDC__-hpcc: ${OUTPUT}__STDC__.hpcc.o ${HPCC_HELPERS}

# CESTC
hello-luca: ${OUTPUT}hello.luca.o ${LUCA_HELPERS}
__GNUC__-luca: ${OUTPUT}__GNUC__.luca.o ${LUCA_HELPERS}
__STDC__-luca: ${OUTPUT}__STDC__.luca.o ${LUCA_HELPERS}
