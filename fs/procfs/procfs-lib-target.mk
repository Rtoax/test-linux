# SPDX-License-Identifier: GPL-3.0

LIBPROCFS_DIR ?= ./

libtest-linux-procfs.a:
	@echo -e "  GEN  \033[1;32m$(@)\033[m"
	${Q}make -C ${LIBPROCFS_DIR} $(@)
	${Q}cp ${LIBPROCFS_DIR}/libtest-linux-procfs.a $(shell pwd)
