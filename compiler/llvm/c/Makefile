# SPDX-License-Identifier: GPL-3.0
HAVE_LLVM := yes

target-y := hello
target-llvm-ll-y := hello_ll

obj-ast := $(addsuffix .ast, $(target-y))
obj-ll := $(addsuffix .ll, $(target-y))
obj-ll.s := $(addsuffix .ll.s, $(target-y))
obj-bc := $(addsuffix .bc, $(target-y))
obj-dis.ll := $(addsuffix .dis.ll, $(target-y))

target-post-y := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-dis.ll}

include ../../../template/main.mk

hello: hello.o
hello_ll: hello.ll
