# SPDX-License-Identifier: GPL-3.0
include dir.mk
include os.mk

make-y := $(shell ls *.mak)
make-y += eval.mak.1
make-y := $(filter-out included.mak,${make-y})

ARGS_eval.mk.1 := Rong Tao

MAKEFLAGS += --include-dir=${TOPDIR}
MAKEFLAGS += --include-dir=${TOPDIR}/template

ARGS_firstword := build
ARGS_MAKECMDGOALS := build rong tao
