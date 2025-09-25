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

sub-dir ?=
kmod-list ?=

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

define git_relative_dir
$(patsubst ${GIT_TOPDIR}/%,%,$(1))
endef

include ${TEMPLATE_DIR}/../elf/pie.mk
ifneq ($(sub-dir)$(kmod-list),)
  include ${TEMPLATE_DIR}/subdir-header.mk
endif

build-targets := $(targets-prep)
build-targets += $(OUTPUT)
build-targets += $(targets-liba) $(targets-libso) $(targets-libso-cpp)
build-targets += $(targets)
build-targets += $(targets-asm)
build-targets += $(targets-cpp)
build-targets += $(targets-llvm-ll)
build-targets += $(targets-bpf)
build-targets += $(targets-rust)
build-targets += $(targets-nvcc)
build-targets += $(targets-hipcc)
build-targets += $(targets-mxcc) $(targets-htcc)
build-targets += $(targets-go)
build-targets += $(targets-java)
targets-shell-logs := $(patsubst %.sh,%.sh.log,$(targets-shell))
build-targets += $(targets-shell-logs)
targets-python-logs := $(patsubst %.py,%.py.log,$(targets-python))
build-targets += $(targets-python-logs)
targets-mk-logs := $(patsubst %.mk,%.mk.log,$(targets-mk))
build-targets += $(targets-mk-logs)
build-targets += $(sub-dir-build) $(kmod-list-build)
build-targets += $(targets-post)

ifdef DEBUG
  $(info build-targets = ${build-targets})
endif

.PHONY: build
build: $(build-targets)
	$(call log_tgt_done,build,$(call git_relative_dir,$(shell realpath .)))

.PHONY: test
test: $(build-targets) $(sub-dir-test) $(kmod-list-test) $(targets-test)
	$(call log_tgt_done,test,$(call git_relative_dir,$(shell realpath .)))

.PHONY: clean
clean: $(sub-dir-clean) $(kmod-list-clean) $(targets-clean)
	$(call log_tgt_start,clean,${build-targets} ${targets-clean})
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
ifneq ($(targets-liba),)
  include ${TEMPLATE_DIR}/targets/liba.mk
endif
ifneq ($(targets-libso)$(targets-libso-cpp),)
  include ${TEMPLATE_DIR}/targets/libso.mk
endif
ifneq ($(HAVE_LLVM)$(targets-llvm-ll),)
  include ${TEMPLATE_DIR}/targets/llvm.mk
endif
ifneq ($(targets-bpf)$(VMLINUX_H),)
  include ${TEMPLATE_DIR}/targets/bpf.mk
endif
ifneq ($(targets-rust),)
  include ${TEMPLATE_DIR}/targets/rust.mk
endif
ifneq ($(targets-nvcc),)
  include ${TEMPLATE_DIR}/targets/nvidia.mk
endif
ifneq ($(targets-hipcc),)
  include ${TEMPLATE_DIR}/targets/amd.mk
endif
ifneq ($(targets-mxcc)$(targets-htcc),)
  include ${TEMPLATE_DIR}/targets/metax.mk
endif
ifneq ($(targets-shell),)
  include ${TEMPLATE_DIR}/targets/shell.mk
endif
ifneq ($(targets-mk-logs),)
  include ${TEMPLATE_DIR}/targets/make.mk
endif
ifneq ($(targets-python),)
  include ${TEMPLATE_DIR}/targets/python.mk
endif
ifneq ($(targets-go),)
  include ${TEMPLATE_DIR}/targets/golang.mk
endif
ifneq ($(targets-java),)
  include ${TEMPLATE_DIR}/targets/java.mk
endif

ifneq ($(sub-dir)$(kmod-list),)
  include ${TEMPLATE_DIR}/subdir-footer.mk
endif
