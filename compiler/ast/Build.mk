# SPDX-License-Identifier: GPL-3.0
target-llvm-ll-y := hello
hello-objs := hello.llvm.ll

target-prep-y += hello.llvm.ast
target-prep-y += hello.llvm.bc
