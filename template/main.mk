# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
CXX ?= g++
Q ?= @

sub-dir ?=

CFLAGS += -D_GNU_SOURCE
CFLAGS += -Werror -Wall
# C special, not for C++
CFLAGS += -Wstrict-prototypes

CXXFLAGS += -D_GNU_SOURCE
CXXFLAGS += -Werror -Wall

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
  MAKEFLAGS += ERROR=1
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
  CXXFLAGS += -Wno-error
  MAKEFLAGS += FORCE=1
endif

ifdef STATIC
  CFLAGS += -static
  CXXFLAGS += -static
  LDFLAGS += -static
  LDXXFLAGS += -static
  MAKEFLAGS += STATIC=1
endif

ifdef DEBUG
  $(info CFLAGS = ${CFLAGS})
  $(info LDFLAGS = ${LDFLAGS})
  $(info CXXFLAGS = ${CXXFLAGS})
  $(info LDXXFLAGS = ${LDXXFLAGS})
endif

TEMPLATE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export TEMPLATE_DIR

include ${TEMPLATE_DIR}/../elf/pie.mk
include ${TEMPLATE_DIR}/../tlbuild.mk
include ${TEMPLATE_DIR}/subdir-header.mk

build-targets := $(TARGETS_PREP)
build-targets += $(OUTPUT)
build-targets += $(TARGETS_LIBA) $(TARGETS_LIBSO)
build-targets += $(TARGETS)
build-targets += $(TARGETS_ASM)
build-targets += $(TARGETS_CPP)
build-targets += $(TARGETS_BPF)
build-targets += $(TARGETS_RUST)
build-targets += $(TARGETS_CUDA)
build-targets += $(TARGETS_GO)
build-targets += $(TARGETS_JAVA)
TARGETS_SHELL_LOGS := $(patsubst %.sh,%.sh.log,$(TARGETS_SHELL))
build-targets += $(TARGETS_SHELL_LOGS)
TARGETS_PYTHON_LOGS := $(patsubst %.py,%.py.log,$(TARGETS_PYTHON))
build-targets += $(TARGETS_PYTHON_LOGS)
TARGETS_MK_LOGS := $(patsubst %.mk,%.mk.log,$(TARGETS_MK))
build-targets += $(TARGETS_MK_LOGS)
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
	${Q}rm -rf ${build-targets} *.o *.opp *.d *.oasm *.oS *.log *.out *.class
	${Q}rm -rf *.so *.so.* *.a
	@echo -e " \033[1;33m Clean $(shell pwd) done \033[m"

include ${TEMPLATE_DIR}/target-exe.mk
ifneq ($(TARGETS_LIBA),)
  include ${TEMPLATE_DIR}/target-liba.mk
endif
ifneq ($(TARGETS_LIBSO),)
  include ${TEMPLATE_DIR}/target-libso.mk
endif
include ${TEMPLATE_DIR}/target-llvm.mk
ifneq ($(TARGETS_BPF),)
  include ${TEMPLATE_DIR}/target-bpf.mk
endif
ifneq ($(TARGETS_RUST),)
  include ${TEMPLATE_DIR}/target-rust.mk
endif
ifneq ($(TARGETS_CUDA),)
  include ${TEMPLATE_DIR}/target-cuda.mk
endif
ifneq ($(TARGETS_SHELL),)
  include ${TEMPLATE_DIR}/target-shell.mk
endif
ifneq ($(TARGETS_MK_LOGS),)
  include ${TEMPLATE_DIR}/target-make.mk
endif
ifneq ($(TARGETS_PYTHON),)
  include ${TEMPLATE_DIR}/target-python.mk
endif
ifneq ($(TARGETS_GO),)
  include ${TEMPLATE_DIR}/target-golang.mk
endif
ifneq ($(TARGETS_JAVA),)
  include ${TEMPLATE_DIR}/target-java.mk
endif
ifneq (${OUTPUT},)
  include ${TEMPLATE_DIR}/target-output.mk
endif

include ${TEMPLATE_DIR}/subdir-footer.mk
