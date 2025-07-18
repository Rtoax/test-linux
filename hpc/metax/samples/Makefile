# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

TARGETS_HTCC := hello
TARGETS_HTCC += parallel
TARGETS_HTCC += hcclGetVersion
TARGETS_HTCC += hcMalloc

LDFLAGS_HTCC := -lhccl

HPCC_HELPERS := ${OUTPUT}hpcc_helpers.hpcc.o

include ../../../template/main.mk

${HPCC_HELPERS}: hpcc_helpers.h

hello: ${OUTPUT}hello.hpcc.o
parallel: ${OUTPUT}parallel.hpcc.o
hcclGetVersion: ${OUTPUT}hcclGetVersion.hpcc.o ${HPCC_HELPERS}
hcMalloc: ${OUTPUT}hcMalloc.hpcc.o ${HPCC_HELPERS}
