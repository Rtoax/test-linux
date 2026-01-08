# SPDX-License-Identifier: GPL-3.0
USE_LLVM = 1

target-y := hello
target-llvm-ll-y := hello_ll

obj-ast := $(addsuffix .llvm.ast, $(target-y))
obj-ll := $(addsuffix .llvm.ll, $(target-y))
obj-ll.s := $(addsuffix .llvm.ll.s, $(target-y))
obj-bc := $(addsuffix .llvm.bc, $(target-y))
obj-dis.ll := $(addsuffix .llvm.dis.ll, $(target-y))

target-post-y := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-dis.ll}

include main.mk

hello: hello.o
hello_ll: hello.llvm.ll
