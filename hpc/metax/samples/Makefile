# SPDX-License-Identifier: GPL-3.0
TARGETS_HTCC := hello
TARGETS_HTCC += parallel
TARGETS_HTCC += hcclGetVersion

LDFLAGS_HTCC := -lhccl

include ../../../template/main.mk

hello: hello.hpcc.o
parallel: parallel.hpcc.o
hcclGetVersion: hcclGetVersion.hpcc.o
