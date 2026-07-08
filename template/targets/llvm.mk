# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Targets list:
# - .llvm.ast
# - .llvm.bc
# - .llvm.bc.dis
# - .llvm.ll
# - .llvm.ll.bc
# - .llvm.ll.s
# - .llvm.s
# - target-llvm-ll-y
#
# Input definitions:
#
ifndef _TARGET_LLVM_MK
_TARGET_LLVM_MK = 1

include clang.mk
include llvm.mk

CLANG_AST_CFLAGS := -Xclang -ast-dump -fsyntax-only

# AST: Abstract Syntax Tree
%.llvm.ast: %.c
	$(call log_obj,${CLANG} AST,$(@))
	${Q}$(CLANG) $(<) ${CLANG_AST_CFLAGS} $(CFLAGS) $(CFLAGS_$(*)) > $(@)

%.llvm.s: %.c
	$(call log_obj,${CLANG} S,$(@))
	${Q}$(CLANG) -S $(<) -o $(@) $(CFLAGS) $(CFLAGS_$(*))

# IR bitcode ascii txt
%.llvm.ll: %.c
	$(call log_obj,${CLANG} LL,$(@))
	${Q}$(CLANG) -S -emit-llvm $(<) -o $(@) $(CFLAGS) $(CFLAGS_$(*))

# IR bitcode
%.llvm.bc: %.c
	$(call log_obj,${CLANG} BC,$(@))
	${Q}$(CLANG) -c -emit-llvm $(<) -o $(@) $(CFLAGS) $(CFLAGS_$(*))

# Generate bitcode from .llvm.ll
%.llvm.ll.bc: %.llvm.ll
	$(call log_obj,${LLVM_AS},$(@))
	${Q}$(LLVM_AS) $(<) -o $(@)

%.llvm.bc.dis: %.llvm.bc
	$(call log_obj,${LLVM_DIS},$(@))
	${Q}$(LLVM_DIS) $(<) -o $(@)

%.llvm.ll.s: %.llvm.ll
	$(call log_obj,${LLC},$(@))
	${Q}$(LLC) $(<) -o $(@)

${target-llvm-ll-y}: %:
	$(call log_tgt,${CLANG} LL,$(@))
	${Q}$(CLANG) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

# depends on .llvm.ll
$(foreach t, ${target-llvm-ll-y}, \
  $(if $(shell test -f ${t}.llvm.ll && echo yes), \
    $(eval ${t}: ${t}.llvm.ll $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
)

endif
