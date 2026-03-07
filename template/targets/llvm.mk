# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Targets list:
# - .llvm.ast
# - .llvm.ll
# - .llvm.bc
# - .llvm.bc.dis
# - .llvm.ll.s
# - target-llvm-ll-y
#
# Input definitions:
#
ifndef _TARGET_LLVM_MK
export _TARGET_LLVM_MK = 1

include llvm.mk

ifeq ($(CLANG),)
  $(error Not found clang, please install clang first)
endif
ifeq ($(LLVM_CONFIG),)
  $(error Not found llvm-config, please install llvm first)
endif

CLANG_AST_CFLAGS := -Xclang -ast-dump -fsyntax-only

# AST: Abstract Syntax Tree
%.llvm.ast: %.c
	$(call log_obj,CLANG AST,$(@))
	${Q}$(CLANG) $(<) ${CLANG_AST_CFLAGS} $(CFLAGS) $(CFLAGS_$(*)) > $(@)

%.llvm.ll: %.c
	$(call log_obj,CLANG LL,$(@))
	${Q}$(CLANG) -S -emit-llvm $(<) -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.llvm.bc: %.llvm.ll
	$(call log_obj,LLVM AS,$(@))
	${Q}$(LLVM_AS) $(<) -o $(@)

%.llvm.bc.dis: %.llvm.bc
	$(call log_obj,LLVM DIS,$(@))
	${Q}$(LLVM_DIS) $(<) -o $(@)

%.llvm.ll.s: %.llvm.ll
	$(call log_obj,LLC,$(@))
	${Q}$(LLC) $(<) -o $(@)

${target-llvm-ll-y}: %:
	$(call log_tgt,LLVM LL,$(@))
	${Q}$(CLANG) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

endif
