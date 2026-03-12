# SPDX-License-Identifier: GPL-3.0
USE_LLVM = 1

target-y := hello
target-llvm-ll-y := hello_ll

obj-ast := $(addsuffix .llvm.ast, $(target-y))
obj-ll := $(addsuffix .llvm.ll, $(target-y))
obj-ll.s := $(addsuffix .llvm.ll.s, $(target-y))
obj-bc := $(addsuffix .llvm.bc, $(target-y))
obj-bc.dis := $(addsuffix .llvm.bc.dis, $(target-y))

target-post-y := ${obj-ast} ${obj-ll} ${obj-ll.s} ${obj-bc} ${obj-bc.dis}
