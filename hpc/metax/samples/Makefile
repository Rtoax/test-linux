# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include ../../../compiler/compiler.mk

targets-htcc := hello
targets-htcc += parallel
targets-htcc += hcclGetVersion
targets-htcc += hcMalloc
targets-htcc += hcMallocManaged
targets-htcc += hcGetDeviceProperties
targets-htcc += hcDeviceGetAttribute
targets-htcc += hcDeviceGetP2PAttribute
targets-htcc += hcEvent
targets-htcc += dim3
targets-htcc += matrix-fp16 matrix-fp32 matrix-fp64 matrix-int8
targets-htcc += blas
targets-htcc += hcblasLtMatmul
targets-htcc += rand
targets-htcc += fft
targets-htcc += sparse
targets-htcc += __GNUC__
targets-htcc += __STDC__
targets-htcc += float
targets-htcc += cooperative
targets-htcc += module

obj-devbin := hello.devbin
obj-devbin += parallel.devbin
obj-fatbin := hello.fatbin
obj-fatbin += parallel.fatbin parallel.hc_fatbin parallel.hcFatBinSegment

targets-post := $(patsubst %,${OUTPUT}%.E.hpcc,$(targets-htcc))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-devbin))
targets-post += $(patsubst %,${OUTPUT}%,$(obj-fatbin))

targets := matrix-c-fp32 matrix-c-fp64
targets += float-c

CFLAGS_HTCC := -Wno-c99-designator
# Remove default so search directory, see ldflags: -Wl,-rpath,/path/to/so/
LDFLAGS_HTCC := -nodefaultrpath

CFLAGS_HTCC_hcGetDeviceProperties := -Wno-string-plus-int

CFLAGS_matrix-fp64 := -DTEST_FP64=1
CFLAGS_matrix-fp32 := -DTEST_FP32=1
CFLAGS_HTCC_matrix-fp64 := -DTEST_FP64=1
CFLAGS_HTCC_matrix-fp32 := -DTEST_FP32=1
CFLAGS_HTCC_matrix-fp16 := -DTEST_FP16=1
CFLAGS_HTCC_matrix-int8 := -DTEST_INT8=1
CFLAGS_HTCC_blas := -Wno-ignored-attributes
CFLAGS_HTCC_hcblasLtMatmul := ${CFLAGS_HTCC_blas}
LDFLAGS_HTCC_hcblasLtMatmul := ${LDFLAGS_HTCC_blas}

CFLAGS_float-c := ${cflags-support-types}
LDFLAGS_float-c := -lm

HPCC_HELPERS := ${OUTPUT}cuda_helpers.hpcc.o

HELPERS := ${HPCC_HELPERS}

include ../../../template/main.mk

${HPCC_HELPERS}: cuda_helpers.h

${OUTPUT}matrix-fp16.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-fp32.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-fp64.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}matrix-int8.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}blas.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}hcblasLtMatmul.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}rand.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}fft.hpcc.o: cuda_adapter.h cuda_helpers.h
${OUTPUT}sparse.hpcc.o: cuda_adapter.h cuda_helpers.h

hello: ${OUTPUT}hello.hpcc.o ${HELPERS}
module: ${OUTPUT}module.hpcc.o ${HELPERS}
dim3: ${OUTPUT}dim3.hpcc.o ${HELPERS}
parallel: ${OUTPUT}parallel.hpcc.o ${HELPERS}
cooperative: ${OUTPUT}cooperative.hpcc.o ${HELPERS}
hcclGetVersion: ${OUTPUT}hcclGetVersion.hpcc.o ${HELPERS}
hcMalloc: ${OUTPUT}hcMalloc.hpcc.o ${HELPERS}
hcMallocManaged: ${OUTPUT}hcMallocManaged.hpcc.o ${HELPERS}
hcGetDeviceProperties: ${OUTPUT}hcGetDeviceProperties.hpcc.o ${HELPERS}
hcDeviceGetAttribute: ${OUTPUT}hcDeviceGetAttribute.hpcc.o ${HELPERS}
hcDeviceGetP2PAttribute: ${OUTPUT}hcDeviceGetP2PAttribute.hpcc.o ${HELPERS}
hcEvent: ${OUTPUT}hcEvent.hpcc.o ${HELPERS}
matrix-fp16: ${OUTPUT}matrix-fp16.hpcc.o ${HELPERS}
matrix-fp32: ${OUTPUT}matrix-fp32.hpcc.o ${HELPERS}
matrix-fp64: ${OUTPUT}matrix-fp64.hpcc.o ${HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.hpcc.o ${HELPERS}
blas: ${OUTPUT}blas.hpcc.o ${HELPERS}
hcblasLtMatmul: ${OUTPUT}hcblasLtMatmul.hpcc.o ${HELPERS}
rand: ${OUTPUT}rand.hpcc.o ${HELPERS}
fft: ${OUTPUT}fft.hpcc.o ${HELPERS}
sparse: ${OUTPUT}sparse.hpcc.o ${HELPERS}
__GNUC__: ${OUTPUT}__GNUC__.hpcc.o ${HELPERS}
__STDC__: ${OUTPUT}__STDC__.hpcc.o ${HELPERS}
float: ${OUTPUT}float.hpcc.o

matrix-c-fp32: ${OUTPUT}matrix-fp32.o
matrix-c-fp64: ${OUTPUT}matrix-fp64.o
float-c: ${OUTPUT}float-c.o
