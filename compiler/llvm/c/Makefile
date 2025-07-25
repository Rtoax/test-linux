# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

targets := hello
targets-llvm-ll := hello_ll

obj-ast := $(addsuffix .ast, $(targets))
obj-ll := $(addsuffix .ll, $(targets))
obj-ll.s := $(addsuffix .ll.s, $(targets))
obj-bc := $(addsuffix .bc, $(targets))
obj-dis.ll := $(addsuffix .dis.ll, $(targets))

targets-post := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-dis.ll}

include ../../../template/main.mk

hello: hello.o
hello_ll: hello.ll
