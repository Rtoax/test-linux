# SPDX-License-Identifier: GPL-3.0

SUBDIR_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

sub-dir ?=

ALL_TARGETS := $(TARGETS) $(TARGETS_LIBA) $(TARGETS_LIBSO)
ALL_TARGETS += $(TARGETS_CPP)
ALL_TARGETS += $(sub-dir-build)
ALL_TARGETS += $(TARGETS_EXTRA)

ifdef DEBUG
  $(info Compile with DEBUG=1)
  CFLAGS += -DDEBUG -O0 -g -ggdb
  CXXFLAGS += -DDEBUG -O0 -g -ggdb
endif
ifdef ERROR
  $(info Compile with ERROR=1)
  CFLAGS += -DERROR=1
  CXXFLAGS += -DERROR=1
endif
ifdef M32
  $(info Compile 32bit ELF)
  CXXFLAGS += -m32 -DM32=1
  CXXFLAGS += -m32 -DM32=1
endif

include ${SUBDIR_DIR}/../tlbuild.mk
include ${SUBDIR_DIR}/subdir-header.mk

.PHONY: build
build: $(ALL_TARGETS) $(sub-dir-build)
	@echo -e " \033[1;33m Build done \033[m"

.PHONY: test
test: $(ALL_TARGETS) $(sub-dir-test) $(TARGETS_TEST)
	@echo -e " \033[1;33m Test done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m${ALL_TARGETS}\033[m"
	${Q}rm -rf ${ALL_TARGETS} *.o *.opp *.d

include ${SUBDIR_DIR}/target-exe.mk
include ${SUBDIR_DIR}/target-liba.mk
include ${SUBDIR_DIR}/target-libso.mk

include ${SUBDIR_DIR}/subdir-footer.mk
