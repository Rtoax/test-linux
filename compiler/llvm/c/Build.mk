# SPDX-License-Identifier: GPL-3.0
target-y := hello
target-llvm-ll-y := hello_ll

hello_ll-objs := hello.llvm.ll

obj-ast := $(addsuffix .llvm.ast, $(target-y))
obj-ll := $(addsuffix .llvm.ll, $(target-y))
obj-ll.s := $(addsuffix .llvm.ll.s, $(target-y))
obj-bc := $(addsuffix .llvm.bc, $(target-y))
obj-bc.dis := $(addsuffix .llvm.bc.dis, $(target-y))
obj-s := $(addsuffix .llvm.s, $(target-y))

post-y := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-bc.dis} ${obj-s}
