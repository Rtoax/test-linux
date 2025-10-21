# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

target-y := hello
target-prep-y := hello.ll
target-prep-y += hello.ast

CC := clang

include ../../template/main.mk

hello: hello.o
