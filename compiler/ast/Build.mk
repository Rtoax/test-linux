# SPDX-License-Identifier: GPL-3.0
target-llvm-ll-y := hello
hello-objs := hello.llvm.ll

prep-y += hello.llvm.ast
prep-y += hello.llvm.bc
