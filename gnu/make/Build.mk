# SPDX-License-Identifier: GPL-3.0
include dir.mk
include os.mk

target-mk-y := $(shell ls *.mak)
target-mk-y += eval.mak.1

ARGS_eval.mk.1 := Rong Tao

MAKEFLAGS += --include-dir=${TOPDIR}
MAKEFLAGS += --include-dir=${TOPDIR}/template

ARGS_firstword := build
ARGS_MAKECMDGOALS := build rong tao
