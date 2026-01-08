# SPDX-License-Identifier: GPL-3.0
USE_LLVM = 1

target-y := hello
target-prep-y := hello.llvm.ll
target-prep-y += hello.llvm.ast

CC := clang

include main.mk

hello: hello.o
