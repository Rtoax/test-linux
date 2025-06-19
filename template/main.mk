# SPDX-License-Identifier: GPL-3.0

TEMPLATE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

sub-dir ?=


ifdef DEBUG
  $(info Compile with DEBUG=1)
  CFLAGS += -DDEBUG -O0 -g -ggdb
  CXXFLAGS += -DDEBUG -O0 -g -ggdb
  MAKEFLAGS += DEBUG=1
endif

ifdef ERROR
  $(info Compile with ERROR=1)
  CFLAGS += -DERROR=1
  CXXFLAGS += -DERROR=1
endif

ifdef M32
  $(info Compile 32bit ELF)
  CFLAGS += -m32 -DM32=1
  CXXFLAGS += -m32 -DM32=1
  LDFLAGS += -m32 -DM32=1
  LDXXFLAGS += -m32 -DM32=1
  MAKEFLAGS += M32=1
endif

ifdef FORCE
  CFLAGS += -Wno-error
endif

include ${TEMPLATE_DIR}/../tlbuild.mk
include ${TEMPLATE_DIR}/subdir-header.mk

build-targets := $(TARGETS_PREP)
build-targets += $(OUTPUT)
build-targets += $(TARGETS) $(TARGETS_LIBA) $(TARGETS_LIBSO)
build-targets += $(TARGETS_CPP)
build-targets += $(sub-dir-build)
build-targets += $(TARGETS_POST)

.PHONY: build
build: $(build-targets)
	@echo -e " \033[1;33m Build $(shell pwd) done \033[m"

.PHONY: test
test: $(build-targets) $(sub-dir-test) $(TARGETS_TEST)
	@echo -e " \033[1;33m Test $(shell pwd) done \033[m"

.PHONY: clean
clean: $(sub-dir-clean) $(TARGETS_CLEAN)
	@echo -e "  CLEAN  \033[1;32m${build-targets} ${TARGETS_CLEAN}\033[m"
	${Q}rm -rf ${build-targets} *.o *.opp *.d
	@echo -e " \033[1;33m Clean $(shell pwd) done \033[m"

include ${TEMPLATE_DIR}/target-exe.mk
include ${TEMPLATE_DIR}/target-liba.mk
include ${TEMPLATE_DIR}/target-libso.mk
ifneq (${OUTPUT},)
  include ${TEMPLATE_DIR}/target-output.mk
endif

include ${TEMPLATE_DIR}/subdir-footer.mk
