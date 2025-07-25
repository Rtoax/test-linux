# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

targets-htcc := hello
targets-htcc += parallel
targets-htcc += hcclGetVersion
targets-htcc += hcMalloc
targets-htcc += hcGetDeviceProperties
targets-htcc += hcDeviceGetAttribute
targets-htcc += hcDeviceGetP2PAttribute
targets-htcc += dim3
targets-htcc += matrix-mul matrix-mul-double

targets-post := $(patsubst %,${OUTPUT}%.E.hpcc,$(targets-htcc))

targets := matrix-mul-c
targets += matrix-mul-c-double

# some code use this macro test pure C
CFLAGS_HTCC := -DHAVE_HCCL=1
LDFLAGS_HTCC := -lhccl

CFLAGS_HTCC_hcGetDeviceProperties := -Wno-string-plus-int

CFLAGS_HTCC_matrix-mul-double := -DTEST_DOUBLE=1

HPCC_HELPERS := ${OUTPUT}hpcc_helpers.hpcc.o

include ../../../template/main.mk

${HPCC_HELPERS}: hpcc_helpers.h

${OUTPUT}matrix-mul.hpcc.o: cuda2hccl.h
${OUTPUT}matrix-mul-double.hpcc.o: cuda2hccl.h

hello: ${OUTPUT}hello.hpcc.o ${HPCC_HELPERS}
dim3: ${OUTPUT}dim3.hpcc.o ${HPCC_HELPERS}
parallel: ${OUTPUT}parallel.hpcc.o ${HPCC_HELPERS}
hcclGetVersion: ${OUTPUT}hcclGetVersion.hpcc.o ${HPCC_HELPERS}
hcMalloc: ${OUTPUT}hcMalloc.hpcc.o ${HPCC_HELPERS}
hcGetDeviceProperties: ${OUTPUT}hcGetDeviceProperties.hpcc.o ${HPCC_HELPERS}
hcDeviceGetAttribute: ${OUTPUT}hcDeviceGetAttribute.hpcc.o ${HPCC_HELPERS}
hcDeviceGetP2PAttribute: ${OUTPUT}hcDeviceGetP2PAttribute.hpcc.o ${HPCC_HELPERS}
matrix-mul: ${OUTPUT}matrix-mul.hpcc.o ${HPCC_HELPERS}
matrix-mul-double: ${OUTPUT}matrix-mul-double.hpcc.o ${HPCC_HELPERS}

matrix-mul-c: ${OUTPUT}matrix-mul.o
matrix-mul-c-double: ${OUTPUT}matrix-mul-double.o
