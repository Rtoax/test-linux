# SPDX-License-Identifier: GPL-3.0
_LLVM = 1

# Yep, i always store it this path
LLVM_SRC_ROOT := /home/rongtao/Git/llvm/
CLANG_SRC_ROOT := ${LLVM_SRC_ROOT}/clang/

ifdef DEBUG
  $(info LLVM_SRC_ROOT = ${LLVM_SRC_ROOT})
  $(info CLANG_SRC_ROOT = ${CLANG_SRC_ROOT})
endif
