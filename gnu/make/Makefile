# SPDX-License-Identifier: GPL-3.0
include ../../template/dir.mk

target-mk-y := $(shell ls *.mk)

MAKEFLAGS += --include-dir=${TOPDIR}

ARGS_firstword := build
ARGS_MAKECMDGOALS := build rong tao

include ../../template/main.mk
