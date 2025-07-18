# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

TARGETS_HTCC := hello
TARGETS_HTCC += parallel
TARGETS_HTCC += hcclGetVersion

LDFLAGS_HTCC := -lhccl

include ../../../template/main.mk

hello: ${OUTPUT}hello.hpcc.o
parallel: ${OUTPUT}parallel.hpcc.o
hcclGetVersion: ${OUTPUT}hcclGetVersion.hpcc.o ${OUTPUT}hpcc_helpers.hpcc.o
