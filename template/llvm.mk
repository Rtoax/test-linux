# SPDX-License-Identifier: GPL-3.0
_LLVM = 1

CLANG := $(shell which clang 2>/dev/null)
CLANG_CXX := $(shell which clang++ 2>/dev/null)

LLVM_CONFIG := $(shell which llvm-config 2>/dev/null)
LLVM_AS := $(shell which llvm-as 2>/dev/null)
LLVM_DIS := $(shell which llvm-dis 2>/dev/null)
LLC := $(shell which llc 2>/dev/null)

# Yep, i always store it this path
LLVM_SRC_ROOT := /home/rongtao/Git/llvm/
CLANG_SRC_ROOT := ${LLVM_SRC_ROOT}/clang/

# $1 - target name
define llvm_support_target
$(shell if [[ $$(${CLANG} -print-target-y | grep -ow $1) == $1 ]]; then echo y; fi)
endef

ifdef DEBUG
  $(info CLANG = ${CLANG})
  $(info CLANG_CXX = ${CLANG_CXX})
  $(info LLVM_CONFIG = ${LLVM_CONFIG})
  $(info LLVM_AS = ${LLVM_AS})
  $(info LLVM_DIS = ${LLVM_DIS})
  $(info LLC = ${LLC})
  $(info LLVM_SRC_ROOT = ${LLVM_SRC_ROOT})
  $(info CLANG_SRC_ROOT = ${CLANG_SRC_ROOT})
  $(info LLVM support NON_EXIST = $(call llvm_support_target,NON_EXIST))
  $(info LLVM support NVPTX = $(call llvm_support_target,nvptx))
  $(info LLVM support NVPTX64 = $(call llvm_support_target,nvptx64))
  $(info LLVM support AMDGCN = $(call llvm_support_target,amdgcn))
endif
