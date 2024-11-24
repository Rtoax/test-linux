# SPDX-License-Identifier: GPL-3.0
SHELL = bash

LIBS_TOPDIR := $(shell git rev-parse --show-toplevel || :)/libs/

CFLAGS += -I${LIBS_TOPDIR}

libtest-linux-c.a:
	@make -C ${LIBS_TOPDIR} $(@)
	@cp ${LIBS_TOPDIR}/libtest-linux-c.a $(shell pwd)
