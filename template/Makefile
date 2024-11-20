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
	@make -f Makefile.user
	@make -f Makefile.subdir
	@mkdir -p build && pushd build && cmake .. && make && popd
	@echo -e " \033[1;33m Building Kernel \033[m"
	@make -f Makefile.kernel

.PHONY: clean
clean:
	@make clean -f Makefile.user
	@make clean -f Makefile.subdir
	@make clean -f Makefile.kernel
	@rm -rf build
