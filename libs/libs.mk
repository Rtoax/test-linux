# SPDX-License-Identifier: GPL-3.0
SHELL = bash

LIBS_DIR ?= ./

libtest-linux-c.a:
	@echo -e "  GEN  \033[1;32m$(@)\033[m"
	${Q}make -C ${LIBS_DIR} $(@)
	${Q}cp ${LIBS_DIR}/libtest-linux-c.a $(shell pwd)
