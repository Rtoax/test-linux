# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

TARGETS := hello
TARGETS_PREP := hello.ll
TARGETS_PREP += hello.ast

CC := clang

include ../../template/main.mk

hello: hello.o
