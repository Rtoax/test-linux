# SPDX-License-Identifier: GPL-3.0
_TARGET_LLVM = 1

CLANG := $(shell which clang 2>/dev/null)
CLANG_CXX := $(shell which clang++ 2>/dev/null)

LLVM_CONFIG := $(shell which llvm-config 2>/dev/null)
LLVM_AS := $(shell which llvm-as 2>/dev/null)
LLVM_DIS := $(shell which llvm-dis 2>/dev/null)
LLC := $(shell which llc 2>/dev/null)

ifeq ($(CLANG),)
  $(error Not found clang, please install clang first)
endif
ifeq ($(LLVM_CONFIG),)
  $(error Not found llvm-config, please install llvm first)
endif

LLVM_CFLAGS += $(shell ${LLVM_CONFIG} --cflags)
LLVM_CXXFLAGS += $(shell ${LLVM_CONFIG} --cxxflags)

LLVM_LDFLAGS += $(shell ${LLVM_CONFIG} --ldflags)

CLANG_AST_CFLAGS := -Xclang -ast-dump -fsyntax-only

# AST: Abstract Syntax Tree
%.ast: %.c
	$(call log_tgt_obj,CLANG AST,$(<),$(@))
	${Q}$(CLANG) $(<) ${CLANG_AST_CFLAGS} $(CFLAGS) $(CFLAGS_$(*)) > $(@)

%.ll: %.c
	$(call log_tgt_obj,CLANG LL,$(<),$(@))
	${Q}$(CLANG) -S -emit-llvm $(<) -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.bc: %.ll
	$(call log_tgt_obj,LLVM AS,$(<),$(@))
	${Q}$(LLVM_AS) $(<) -o $(@)

%.dis.ll: %.bc
	$(call log_tgt_obj,LLVM DIS,$(<),$(@))
	${Q}$(LLVM_DIS) $(<) -o $(@)

%.ll.s: %.ll
	$(call log_tgt_obj,LLC,$(<),$(@))
	${Q}$(LLC) $(<) -o $(@)

${targets-llvm-ll}: %:
	$(call log_tgt_exe,LLVM LL,$(<),$(@))
	${Q}$(CLANG) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))
