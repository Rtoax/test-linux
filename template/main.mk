# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao
_MAIN = 1

CC ?= gcc
CC_PFX ?=
CXX ?= g++
OBJCOPY ?= objcopy
Q ?= @
SHELL := bash

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | tr -d '"')
ifeq ($(shell uname -m),x86_64)
else ifeq ($(shell uname -m),aarch64)
endif

subdir-y ?=

CFLAGS += -D_GNU_SOURCE
CFLAGS += -Werror -Wall
# C special, not for C++
CFLAGS += -Wstrict-prototypes

CXXFLAGS += -D_GNU_SOURCE
CXXFLAGS += -Werror -Wall

ifdef DEBUG
  $(info Compile with DEBUG=1)
  CFLAGS += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS += -DDEBUG=${DEBUG} -O0 -g -ggdb
  MAKEFLAGS += DEBUG=${DEBUG}
endif

ifdef ERROR
  $(info Compile with ERROR=${ERROR})
  CFLAGS += -DERROR=${ERROR}
  CXXFLAGS += -DERROR=${ERROR}
  MAKEFLAGS += ERROR=${ERROR}
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

CFLAGS_PIE :=
LDFLAGS_PIE :=
# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifdef PIE
  # clang: not support -pie in cflags
  ifeq ($(CC),gcc)
    CFLAGS_PIE += -pie
  endif
  CFLAGS_PIE += -fPIE
  LDFLAGS_PIE += -pie -fPIE
  MAKEFLAGS += PIE=1
endif

ifdef NOPIE
  CFLAGS_PIE += -no-pie
  LDFLAGS_PIE += -no-pie
  MAKEFLAGS += NOPIE=1
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif
CFLAGS += ${CFLAGS_PIE}
LDFLAGS += ${LDFLAGS_PIE}

ifdef DEBUG
  $(info CFLAGS = ${CFLAGS})
  $(info LDFLAGS = ${LDFLAGS})
  $(info CXXFLAGS = ${CXXFLAGS})
  $(info LDXXFLAGS = ${LDXXFLAGS})
endif

export CFLAGS LDFLAGS CXXFLAGS LDXXFLAGS CFLAGS_PIE LDFLAGS_PIE MAKEFLAGS

TEMPLATE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export TEMPLATE_DIR

include ${TEMPLATE_DIR}/ansi.mk
include ${TEMPLATE_DIR}/verbose.mk
include ${TEMPLATE_DIR}/arch.mk
include ${TEMPLATE_DIR}/dir.mk
include ${TEMPLATE_DIR}/log.mk

include ${TEMPLATE_DIR}/../elf/pie.mk
ifneq ($(subdir-y),)
  include ${TEMPLATE_DIR}/subdir-header.mk
endif

build-targets := $(target-prep-y)
build-targets += $(OUTPUT)
build-targets += $(target-liba-y) $(target-libso-y) $(target-libso-cpp-y)
build-targets += $(target-y)
build-targets += $(target-asm-y)
build-targets += $(target-cpp-y)
build-targets += $(target-llvm-ll-y)
build-targets += $(target-bpf-y)
build-targets += $(target-rust-y)
build-targets += $(target-nvcc-y)
build-targets += $(target-hipcc-y)
build-targets += $(target-mxcc-y) $(target-htcc-y)
build-targets += $(target-lscc-y)
build-targets += $(target-go-y)
build-targets += $(target-java-y)
target-shell-logs := $(patsubst %.sh,%.sh.log,$(target-shell-y))
build-targets += $(target-shell-logs)
target-python-logs := $(patsubst %.py,%.py.log,$(target-python-y))
build-targets += $(target-python-logs)
target-mk-logs := $(patsubst %.mk,%.mk.log,$(target-mk-y))
build-targets += $(target-mk-logs)
build-targets += $(subdir-y-build)
build-targets += $(target-post-y)

ifdef DEBUG
  $(info build-targets = ${build-targets})
endif

.PHONY: build
build: $(build-targets)
	$(call log_tgt_done,build,$(call git_relative_dir,$(shell realpath .)))

.PHONY: test
test: $(build-targets) $(subdir-y-test) $(target-test-y)
	$(call log_tgt_done,test,$(call git_relative_dir,$(shell realpath .)))

.PHONY: clean
clean: $(subdir-y-clean) $(target-clean-y)
	$(call log_tgt_start,clean,${build-targets} ${target-clean-y})
	${Q}rm -rf ${build-targets}
	${Q}rm -f *.o *.log *.out *.class
	${Q}rm -f *.so *.so.* *.a
	${Q}rm -f *.dat *.bin
	${Q}rm -f ${VMLINUX_H}
	$(call log_tgt_done,clean,$(call git_relative_dir,$(shell realpath .)))

ifneq (${OUTPUT},)
  include ${TEMPLATE_DIR}/targets/output.mk
endif
include ${TEMPLATE_DIR}/targets/exe.mk
ifneq ($(target-liba-y),)
  include ${TEMPLATE_DIR}/targets/liba.mk
endif
ifneq ($(target-libso-y)$(target-libso-cpp-y),)
  include ${TEMPLATE_DIR}/targets/libso.mk
endif
ifneq ($(HAVE_LLVM)$(target-llvm-ll-y),)
  include ${TEMPLATE_DIR}/targets/llvm.mk
endif
ifneq ($(target-bpf-y)$(VMLINUX_H),)
  include ${TEMPLATE_DIR}/targets/bpf.mk
endif
ifneq ($(target-rust-y),)
  include ${TEMPLATE_DIR}/targets/rust.mk
endif
ifneq ($(target-nvcc-y),)
  include ${TEMPLATE_DIR}/targets/nvidia.mk
endif
ifneq ($(target-hipcc-y),)
  include ${TEMPLATE_DIR}/targets/amd.mk
endif
ifneq ($(target-mxcc-y)$(target-htcc-y),)
  include ${TEMPLATE_DIR}/targets/metax.mk
endif
ifneq ($(target-lscc-y),)
  include ${TEMPLATE_DIR}/targets/cestc.mk
endif
ifneq ($(target-shell-y),)
  include ${TEMPLATE_DIR}/targets/shell.mk
endif
ifneq ($(target-mk-y),)
  include ${TEMPLATE_DIR}/targets/make.mk
endif
ifneq ($(target-python-y),)
  include ${TEMPLATE_DIR}/targets/python.mk
endif
ifneq ($(target-go-y),)
  include ${TEMPLATE_DIR}/targets/golang.mk
endif
ifneq ($(target-java-y),)
  include ${TEMPLATE_DIR}/targets/java.mk
endif

ifneq ($(subdir-y),)
  include ${TEMPLATE_DIR}/subdir-footer.mk
endif
