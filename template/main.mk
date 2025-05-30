# SPDX-License-Identifier: GPL-3.0

SUBDIR_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

sub-dir ?=

include ${SUBDIR_DIR}/../tlbuild.mk
include ${SUBDIR_DIR}/subdir-header.mk

.PHONY: build
build: $(TARGETS) $(TARGETS_LIBA) $(TARGETS_LIBSO) $(sub-dir-build) $(TARGETS_EXTRA)
	@echo -e " \033[1;33m Build done \033[m"

.PHONY: test
test: $(TARGETS) $(TARGETS_LIBA) $(TARGETS_LIBSO) $(sub-dir-test)
	@echo -e " \033[1;33m Test done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m${TARGETS} ${TARGETS_LIBA} ${TARGETS_LIBSO} ${TARGETS_EXTRA}\033[m"
	${Q}rm -rf ${TARGETS} ${TARGETS_LIBA} ${TARGETS_LIBSO} ${TARGETS_EXTRA} *.o *.d

include ${SUBDIR_DIR}/target-exe.mk
include ${SUBDIR_DIR}/target-liba.mk
include ${SUBDIR_DIR}/target-libso.mk

include ${SUBDIR_DIR}/subdir-footer.mk
