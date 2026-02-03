# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - WHEREIS_LLVM=[/usr/include/llvm]
# - HAVE_LLVM=[y|n]
# - LLVM_CONFIG=[/usr/bin/llvm-config]
# - LLVM_AS=[/usr/bin/llvm-as]
# - LLVM_DIS=[/usr/bin/llvm-dis]
# - LLVM_SRC_ROOT=
# - CLANG_SRC_ROOT=
# - llvm-cflags=
# - llvm-cxxflags=
# - llvm-ldflags=
#
# Functions:
# - llvm_support_target()
#
ifndef _LLVM_MK
_LLVM_MK = 1

include shell.mk
include clang.mk

WHEREIS_LLVM := $(shell whereis llvm | awk '{print $$2}')

ifeq (${WHEREIS_LLVM},)
  $(warning "Not found llvm, maybe you should install llvm first")
  export HAVE_LLVM := n
else # Found llvm

LLVM_CONFIG := $(shell which llvm-config 2>/dev/null)
LLVM_AS := $(shell which llvm-as 2>/dev/null)
LLVM_DIS := $(shell which llvm-dis 2>/dev/null)
LLVM_OBJDUMP := $(shell which llvm-objdump 2>/dev/null)
LLC := $(shell which llc 2>/dev/null)

# Note: Yep, i always store under this path
LLVM_SRC_ROOT := $(HOME)/Git/llvm/
CLANG_SRC_ROOT := ${LLVM_SRC_ROOT}/clang/

llvm-cflags := $(shell ${LLVM_CONFIG} --cflags)
llvm-cxxflags := $(shell ${LLVM_CONFIG} --cxxflags)
llvm-ldflags := $(shell ${LLVM_CONFIG} --ldflags)

# $1 - target name
define llvm_support_target
$(shell if [[ $$(${CLANG} -print-targets | grep -ow $1) == $1 ]]; then echo y; fi)
endef

ifdef DEBUG
  $(info LLVM_CONFIG = ${LLVM_CONFIG})
  $(info LLVM_AS = ${LLVM_AS})
  $(info LLVM_DIS = ${LLVM_DIS})
  $(info LLC = ${LLC})
  $(info LLVM_SRC_ROOT = ${LLVM_SRC_ROOT})
  $(info CLANG_SRC_ROOT = ${CLANG_SRC_ROOT})
  $(info llvm-cflags = ${llvm-cflags})
  $(info llvm-cxxflags = ${llvm-cxxflags})
  $(info llvm-ldflags = ${llvm-ldflags})
  $(info LLVM support NON_EXIST = $(call llvm_support_target,NON_EXIST))
  $(info LLVM support NVPTX = $(call llvm_support_target,nvptx))
  $(info LLVM support NVPTX64 = $(call llvm_support_target,nvptx64))
  $(info LLVM support AMDGCN = $(call llvm_support_target,amdgcn))
endif # end of DEBUG

export HAVE_LLVM := y
export LLVM_CONFIG LLVM_AS LLVM_DIS LLC
export LLVM_SRC_ROOT CLANG_SRC_ROOT

endif # end of found WHEREIS_LLVM

endif # end of _LLVM_MK
