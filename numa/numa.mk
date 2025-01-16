# SPDX-License-Identifier: GPL-3.0
SHELL = bash

NUMA_DIR ?= ./

libtest-linux-numa.a:
	@echo -e "  GEN  \033[1;32m$(@)\033[m"
	${Q}make -C ${NUMA_DIR} $(@)
	${Q}cp ${NUMA_DIR}/libtest-linux-numa.a $(shell pwd)
