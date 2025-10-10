# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

__IGNORE_NOTFOUND_ERROR__ := 1

include ../../../../compiler/compiler.mk
include ../cuda.mk
include ../../../amd/rocm/rocm.mk
include ../../../metax/hpcc.mk

ifdef HAVE_CUDA
  targets-nvcc := hello
  targets-nvcc += dim3
  targets-nvcc += cooperative
  targets-nvcc += parallel
  targets-nvcc += cudaMalloc
  targets-nvcc += cudaMallocManaged
  targets-nvcc += cudaGetDeviceCount
  targets-nvcc += cudaGetDeviceProperties
  targets-nvcc += cudaDeviceGetP2PAttribute
  targets-nvcc += cudaDeviceGetAttribute
  targets-nvcc += cudaEvent
  targets-nvcc += cublasLtMatmul
  targets-nvcc += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
  targets-nvcc += blas
  targets-nvcc += rand
  targets-nvcc += fft
  targets-nvcc += sparse
  targets-nvcc += __GNUC__ __STDC__
  targets-nvcc += module
  targets-nvcc += float

  # NCCL
  ifdef HAVE_NCCL
    targets-nvcc += ncclGetVersion
  endif

  obj-cubin := hello.cubin
  obj-cubin += parallel.cubin
  obj-fatbin := hello.fatbin
  obj-fatbin += parallel.fatbin parallel.nv_fatbin parallel.nvFatBinSegment
endif

ifdef HAVE_HIP
  rocm-hipcc := hello
  rocm-hipcc += blas
  rocm-hipcc += dim3
  rocm-hipcc += fft
  rocm-hipcc += sparse
  rocm-hipcc += rand
  rocm-hipcc += parallel
  rocm-hipcc += module
  rocm-hipcc += float
  rocm-hipcc += cooperative
  rocm-hipcc += matrix-fp32
  rocm-hipcc += hipEvent
  rocm-hipcc += hipMalloc
  rocm-hipcc += hipMallocManaged
  rocm-hipcc += hipblasLtMatmul
  rocm-hipcc += hipGetDeviceProperties
  rocm-hipcc += hipGetDeviceCount
  rocm-hipcc += hipDeviceGetP2PAttribute
  rocm-hipcc += __GNUC__

  # RCCL
  rocm-hipcc += ncclGetVersion

  rocm-fatbin := parallel.hip_fatbin parallel.hipFatBinSegment

  targets-hipcc := $(patsubst %,%-hip,$(rocm-hipcc))
endif

ifdef HAVE_HPCC
  metax-htcc := blas
  metax-htcc += hello
  metax-htcc += parallel
  metax-htcc += hcMalloc
  metax-htcc += hcMallocManaged
  metax-htcc += hcGetDeviceCount
  metax-htcc += hcGetDeviceProperties
  metax-htcc += hcDeviceGetAttribute
  metax-htcc += hcDeviceGetP2PAttribute
  metax-htcc += hcEvent
  metax-htcc += dim3
  metax-htcc += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
  metax-htcc += hcblasLtMatmul
  metax-htcc += rand
  metax-htcc += fft
  metax-htcc += sparse
  metax-htcc += __GNUC__
  metax-htcc += __STDC__
  metax-htcc += float
  metax-htcc += cooperative
  metax-htcc += module

  # HCCL
  metax-htcc += hcclGetVersion

  metax-devbin := hello.devbin
  metax-devbin += parallel.devbin
  metax-fatbin := hello.hpcc.fatbin
  metax-fatbin += parallel.hpcc.fatbin
  metax-fatbin += parallel-hpcc.hc_fatbin
  metax-fatbin += parallel-hpcc.hcFatBinSegment

  targets-htcc := $(patsubst %,%-hpcc,$(metax-htcc))
endif

targets-post := $(patsubst %,${OUTPUT}%.E.cu,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.sass.dump,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.ptx.dump,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.ptx,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(targets-nvcc))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-cubin))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-fatbin))
# ROCm HIP
targets-post += $(patsubst %,${OUTPUT}%,$(rocm-fatbin))
# MetaX
targets-post += $(patsubst %,${OUTPUT}%.E.hpcc,$(metax-htcc))
targets-post += $(patsubst %,${OUTPUT}%,$(metax-devbin))
targets-post += $(patsubst %,${OUTPUT}%,$(metax-fatbin))

# Pure C
targets := matrix-c-fp32 matrix-c-fp64
targets += float-c

CFLAGS_matrix-fp64 := -DTEST_FP64=1
CFLAGS_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_NVCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_NVCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_NVCC_matrix-int8 := -DTEST_INT8=1
# NOTE: warning: ‘CUresult cuDeviceComputeCapability(int*, int*, CUdevice)’ is deprecated [-Wdeprecated-declarations]
CFLAGS_NVCC_cudaGetDeviceProperties := -Wno-deprecated-declarations

CUDA_HELPERS := ${OUTPUT}cuda_helpers.cu.o
HIP_HELPERS := ${OUTPUT}cuda_helpers.hip.o
HPCC_HELPERS := ${OUTPUT}cuda_helpers.hpcc.o

CFLAGS_float-c := ${cflags-support-types}
LDFLAGS_float-c := -lm

# FIXME: on my fedora 42 env:
# fatal error: 'bits/c++config.h' file not found
CFLAGS_HIPCC := -I/usr/include/c++/15/x86_64-redhat-linux/
CFLAGS_HIPCC += -I.
CFLAGS_HIPCC += -Wno-unused-result

CFLAGS_HIPCC_matrix-fp32 := -DTEST_FP32=1

CFLAGS_HTCC := -Wno-c99-designator
# Remove default so search directory, see ldflags: -Wl,-rpath,/path/to/so/
LDFLAGS_HTCC := -nodefaultrpath

CFLAGS_HTCC_hcGetDeviceProperties := -Wno-string-plus-int

CFLAGS_HTCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_HTCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_HTCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_HTCC_matrix-int8 := -DTEST_INT8=1
CFLAGS_HTCC_hcblasLtMatmul := ${CFLAGS_HTCC_blas}

CFLAGS_HTCC_blas := -Wno-ignored-attributes
CFLAGS_HTCC_hcblasLtMatmul := ${CFLAGS_HTCC_blas}

include ../../../../template/main.mk

${CUDA_HELPERS}: cuda_helpers.h
${HIP_HELPERS}: cuda_helpers.h
${HPCC_HELPERS}: cuda_helpers.h

dim3: ${OUTPUT}dim3.cu.o ${CUDA_HELPERS}
cooperative: ${OUTPUT}cooperative.cu.o ${CUDA_HELPERS}
blas: ${OUTPUT}blas.cu.o ${CUDA_HELPERS}
cublasLtMatmul: ${OUTPUT}cublasLtMatmul.cu.o ${CUDA_HELPERS}
rand: ${OUTPUT}rand.cu.o ${CUDA_HELPERS}
ncclGetVersion: ${OUTPUT}ncclGetVersion.cu.o ${CUDA_HELPERS}
fft: ${OUTPUT}fft.cu.o ${CUDA_HELPERS}
sparse: ${OUTPUT}sparse.cu.o ${CUDA_HELPERS}
hello: ${OUTPUT}hello.cu.o ${CUDA_HELPERS}
module: ${OUTPUT}module.cu.o ${CUDA_HELPERS}
float: ${OUTPUT}float.cu.o
parallel: ${OUTPUT}parallel.cu.o ${CUDA_HELPERS}
cudaMalloc: ${OUTPUT}cudaMalloc.cu.o ${CUDA_HELPERS}
cudaMallocManaged: ${OUTPUT}cudaMallocManaged.cu.o ${CUDA_HELPERS}
cudaGetDeviceProperties: ${OUTPUT}cudaGetDeviceProperties.cu.o ${CUDA_HELPERS}
cudaGetDeviceCount: ${OUTPUT}cudaGetDeviceCount.cu.o ${CUDA_HELPERS}
cudaDeviceGetP2PAttribute: ${OUTPUT}cudaDeviceGetP2PAttribute.cu.o ${CUDA_HELPERS}
cudaDeviceGetAttribute: ${OUTPUT}cudaDeviceGetAttribute.cu.o ${CUDA_HELPERS}
cudaEvent: ${OUTPUT}cudaEvent.cu.o ${CUDA_HELPERS}
matrix-fp16: ${OUTPUT}matrix-fp16.cu.o ${CUDA_HELPERS}
matrix-fp32: ${OUTPUT}matrix-fp32.cu.o ${CUDA_HELPERS}
matrix-fp64: ${OUTPUT}matrix-fp64.cu.o ${CUDA_HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.cu.o ${CUDA_HELPERS}
matrix-c-fp32: ${OUTPUT}matrix-fp32.o
matrix-c-fp64: ${OUTPUT}matrix-fp64.o
float-c: ${OUTPUT}float-c.o
__GNUC__: ${OUTPUT}__GNUC__.cu.o
__STDC__: ${OUTPUT}__STDC__.cu.o

# ROCm HIP
${OUTPUT}hello.hip.o: hello.cu
hello-hip: ${OUTPUT}hello.hip.o ${HIP_HELPERS}
${OUTPUT}dim3.hip.o: dim3.cu
dim3-hip: ${OUTPUT}dim3.hip.o ${HIP_HELPERS}
__GNUC__-hip: ${OUTPUT}__GNUC__.hip.o ${HIP_HELPERS}
${OUTPUT}fft.hip.o: fft.cu
fft-hip: ${OUTPUT}fft.hip.o ${HIP_HELPERS}
${OUTPUT}blas.hip.o: blas.cu
blas-hip: ${OUTPUT}blas.hip.o ${HIP_HELPERS}
${OUTPUT}cooperative.hip.o: cooperative.cu
cooperative-hip: ${OUTPUT}cooperative.hip.o ${HIP_HELPERS}
${OUTPUT}float.hip.o: float.cu
float-hip: ${OUTPUT}float.hip.o ${HIP_HELPERS}
${OUTPUT}rand.hip.o: rand.cu
rand-hip: ${OUTPUT}rand.hip.o ${HIP_HELPERS}
${OUTPUT}sparse.hip.o: sparse.cu
sparse-hip: ${OUTPUT}sparse.hip.o ${HIP_HELPERS}
${OUTPUT}parallel.hip.o: parallel.cu
parallel-hip: ${OUTPUT}parallel.hip.o ${HIP_HELPERS}
${OUTPUT}module.hip.o: module.cu
module-hip: ${OUTPUT}module.hip.o ${HIP_HELPERS}
${OUTPUT}hipblasLtMatmul.hip.o: cublasLtMatmul.cu
hipblasLtMatmul-hip: ${OUTPUT}hipblasLtMatmul.hip.o ${HIP_HELPERS}
${OUTPUT}hipEvent.hip.o: cudaEvent.cu
hipEvent-hip: ${OUTPUT}hipEvent.hip.o ${HIP_HELPERS}
${OUTPUT}hipMalloc.hip.o: cudaMalloc.cu
hipMalloc-hip: ${OUTPUT}hipMalloc.hip.o ${HIP_HELPERS}
${OUTPUT}hipMallocManaged.hip.o: cudaMallocManaged.cu
hipMallocManaged-hip: ${OUTPUT}hipMallocManaged.hip.o ${HIP_HELPERS}
${OUTPUT}matrix-fp32.hip.o: matrix.cu
matrix-fp32-hip: ${OUTPUT}matrix-fp32.hip.o ${HIP_HELPERS}
${OUTPUT}hipGetDeviceProperties.hip.o: matrix.cu
hipGetDeviceProperties-hip: ${OUTPUT}hipGetDeviceProperties.hip.o ${HIP_HELPERS}
${OUTPUT}hipGetDeviceCount.hip.o: cudaGetDeviceCount.cu
hipGetDeviceCount-hip: ${OUTPUT}hipGetDeviceCount.hip.o ${HIP_HELPERS}
${OUTPUT}hipDeviceGetP2PAttribute.hip.o: cudaDeviceGetP2PAttribute.cu
hipDeviceGetP2PAttribute-hip: ${OUTPUT}hipDeviceGetP2PAttribute.hip.o ${HIP_HELPERS}
${OUTPUT}ncclGetVersion.hip.o: ncclGetVersion.cu
ncclGetVersion-hip: ${OUTPUT}ncclGetVersion.hip.o

# MetaX HPCC
${OUTPUT}matrix-fp16.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-fp32.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-fp64.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-int8.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}hcblasLtMatmul.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}rand.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}fft.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}sparse.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}blas.hpcc.o: blas.cu
${OUTPUT}hcGetDeviceCount.hpcc.o: cudaGetDeviceCount.cu
${OUTPUT}hcclGetVersion.hpcc.o: ncclGetVersion.cu
blas-hpcc: ${OUTPUT}blas.hpcc.o ${HPCC_HELPERS}
hello-hpcc: ${OUTPUT}hello.hpcc.o ${HPCC_HELPERS}
module-hpcc: ${OUTPUT}module.hpcc.o ${HPCC_HELPERS}
dim3-hpcc: ${OUTPUT}dim3.hpcc.o ${HPCC_HELPERS}
parallel-hpcc: ${OUTPUT}parallel.hpcc.o ${HPCC_HELPERS}
cooperative-hpcc: ${OUTPUT}cooperative.hpcc.o ${HPCC_HELPERS}
hcclGetVersion-hpcc: ${OUTPUT}hcclGetVersion.hpcc.o ${HPCC_HELPERS}
hcMalloc-hpcc: ${OUTPUT}hcMalloc.hpcc.o ${HPCC_HELPERS}
hcMallocManaged-hpcc: ${OUTPUT}hcMallocManaged.hpcc.o ${HPCC_HELPERS}
hcclGetVersion-hpcc: ${OUTPUT}hcclGetVersion.hpcc.o ${HPCC_HELPERS}
hcGetDeviceCount-hpcc: ${OUTPUT}hcGetDeviceCount.hpcc.o ${HPCC_HELPERS}
hcGetDeviceProperties-hpcc: ${OUTPUT}hcGetDeviceProperties.hpcc.o ${HPCC_HELPERS}
hcDeviceGetAttribute-hpcc: ${OUTPUT}hcDeviceGetAttribute.hpcc.o ${HPCC_HELPERS}
hcDeviceGetP2PAttribute-hpcc: ${OUTPUT}hcDeviceGetP2PAttribute.hpcc.o ${HPCC_HELPERS}
hcEvent-hpcc: ${OUTPUT}hcEvent.hpcc.o ${HPCC_HELPERS}
matrix-fp16-hpcc: ${OUTPUT}matrix-fp16.hpcc.o ${HPCC_HELPERS}
matrix-fp32-hpcc: ${OUTPUT}matrix-fp32.hpcc.o ${HPCC_HELPERS}
matrix-fp64-hpcc: ${OUTPUT}matrix-fp64.hpcc.o ${HPCC_HELPERS}
matrix-int8-hpcc: ${OUTPUT}matrix-int8.hpcc.o ${HPCC_HELPERS}
hcblasLtMatmul-hpcc: ${OUTPUT}hcblasLtMatmul.hpcc.o ${HPCC_HELPERS}
rand-hpcc: ${OUTPUT}rand.hpcc.o ${HPCC_HELPERS}
fft-hpcc: ${OUTPUT}fft.hpcc.o ${HPCC_HELPERS}
sparse-hpcc: ${OUTPUT}sparse.hpcc.o ${HPCC_HELPERS}
__GNUC__-hpcc: ${OUTPUT}__GNUC__.hpcc.o ${HPCC_HELPERS}
__STDC__-hpcc: ${OUTPUT}__STDC__.hpcc.o ${HPCC_HELPERS}
float-hpcc: ${OUTPUT}float.hpcc.o
