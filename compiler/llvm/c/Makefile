# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

TARGETS := hello
TARGETS_LLVM_LL := hello_ll

obj-ast := $(addsuffix .ast, $(TARGETS))
obj-ll := $(addsuffix .ll, $(TARGETS))
obj-ll.s := $(addsuffix .ll.s, $(TARGETS))
obj-bc := $(addsuffix .bc, $(TARGETS))
obj-dis.ll := $(addsuffix .dis.ll, $(TARGETS))

TARGETS_POST := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-dis.ll}

include ../../../template/main.mk

hello: hello.o
hello_ll: hello.ll
