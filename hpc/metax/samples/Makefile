# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets-htcc := hello
targets-htcc += parallel
targets-htcc += hcclGetVersion
targets-htcc += hcMalloc
targets-htcc += hcGetDeviceProperties
targets-htcc += hcDeviceGetAttribute
targets-htcc += hcDeviceGetP2PAttribute
targets-htcc += hcEvent
targets-htcc += dim3
targets-htcc += matrix matrix-double matrix-int8 matrix-fp16
targets-htcc += blas blas-double
targets-htcc += rand

targets-post := $(patsubst %,${OUTPUT}%.E.hpcc,$(targets-htcc))

targets := matrix-c
targets += matrix-c-double

# some code use this macro test pure C
CFLAGS_HTCC := -DHAVE_HCCL=1
CFLAGS_HTCC += -Wno-c99-designator
LDFLAGS_HTCC := -lhccl

CFLAGS_HTCC_hcGetDeviceProperties := -Wno-string-plus-int

CFLAGS_HTCC_matrix-double := -DTEST_DOUBLE=1
CFLAGS_HTCC_matrix-int8 := -DTEST_INT8=1
CFLAGS_HTCC_matrix-fp16 := -DTEST_FP16=1
LDFLAGS_HTCC_blas := -lhcblas
CFLAGS_HTCC_blas-double := -DTEST_DOUBLE=1
LDFLAGS_HTCC_blas-double := -lhcblas
LDFLAGS_HTCC_rand := -lhcrand

HPCC_HELPERS := ${OUTPUT}hpcc_helpers.hpcc.o

include ../../../template/main.mk

${HPCC_HELPERS}: hpcc_helpers.h

${OUTPUT}matrix.hpcc.o: cuda2hccl.h
${OUTPUT}matrix-double.hpcc.o: cuda2hccl.h
${OUTPUT}matrix-int8.hpcc.o: cuda2hccl.h
${OUTPUT}matrix-fp16.hpcc.o: cuda2hccl.h
${OUTPUT}blas.hpcc.o: cuda2hccl.h
${OUTPUT}blas-double.hpcc.o: cuda2hccl.h
${OUTPUT}rand.hpcc.o: cuda2hccl.h

hello: ${OUTPUT}hello.hpcc.o ${HPCC_HELPERS}
dim3: ${OUTPUT}dim3.hpcc.o ${HPCC_HELPERS}
parallel: ${OUTPUT}parallel.hpcc.o ${HPCC_HELPERS}
hcclGetVersion: ${OUTPUT}hcclGetVersion.hpcc.o ${HPCC_HELPERS}
hcMalloc: ${OUTPUT}hcMalloc.hpcc.o ${HPCC_HELPERS}
hcGetDeviceProperties: ${OUTPUT}hcGetDeviceProperties.hpcc.o ${HPCC_HELPERS}
hcDeviceGetAttribute: ${OUTPUT}hcDeviceGetAttribute.hpcc.o ${HPCC_HELPERS}
hcDeviceGetP2PAttribute: ${OUTPUT}hcDeviceGetP2PAttribute.hpcc.o ${HPCC_HELPERS}
hcEvent: ${OUTPUT}hcEvent.hpcc.o ${HPCC_HELPERS}
matrix: ${OUTPUT}matrix.hpcc.o ${HPCC_HELPERS}
matrix-double: ${OUTPUT}matrix-double.hpcc.o ${HPCC_HELPERS}
matrix-int8: ${OUTPUT}matrix-int8.hpcc.o ${HPCC_HELPERS}
matrix-fp16: ${OUTPUT}matrix-fp16.hpcc.o ${HPCC_HELPERS}
blas: ${OUTPUT}blas.hpcc.o ${HPCC_HELPERS}
blas-double: ${OUTPUT}blas-double.hpcc.o ${HPCC_HELPERS}
rand: ${OUTPUT}rand.hpcc.o ${HPCC_HELPERS}

matrix-c: ${OUTPUT}matrix.o
matrix-c-double: ${OUTPUT}matrix-double.o
