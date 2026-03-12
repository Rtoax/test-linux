# SPDX-License-Identifier: GPL-3.0
include dir.mk
include os.mk

target-mk-y := $(shell ls *.mak)
target-mk-y += eval.mak.1

ARGS_eval.mk.1 := Rong Tao

target-shell-y := version.sh version.sh.1 version.sh.2

SHELL_ARGS_version.sh.1 := --major
SHELL_ARGS_version.sh.2 := --minor

MAKEFLAGS += --include-dir=${TOPDIR}
MAKEFLAGS += --include-dir=${TOPDIR}/template

ARGS_firstword := build
ARGS_MAKECMDGOALS := build rong tao
