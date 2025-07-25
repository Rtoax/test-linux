# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

targets := hello
targets-prep := hello.ll
targets-prep += hello.ast

CC := clang

include ../../template/main.mk

hello: hello.o
