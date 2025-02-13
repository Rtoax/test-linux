# SPDX-License-Identifier: GPL-3.0
SHELL = /bin/bash

$(info INFO: This is info)
$(info INFO: USER_FAILED_LOG = ${USER_FAILED_LOG})
$(info INFO: KERNEL_FAILED_LOG = ${KERNEL_FAILED_LOG})
$(warning WARNING: This is warning)
#$(error ERROR: This error)

.PHONY: all
all:
	@echo -e " \033[1;33m Building User \033[m"
	${Q}make -f Makefile.user
	${Q}make -f Makefile.subdir
	${Q}mkdir -p build && pushd build && cmake .. && make && popd
	@echo -e " \033[1;33m Building Kernel \033[m"
	${Q}make -f Makefile.kernel

.PHONY: clean
clean:
	${Q}make clean -f Makefile.user
	${Q}make clean -f Makefile.subdir
	${Q}make clean -f Makefile.kernel
	${Q}rm -rf build
