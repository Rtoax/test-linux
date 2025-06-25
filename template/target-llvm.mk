# SPDX-License-Identifier: GPL-3.0
CLANG ?= $(shell which clang 2>/dev/null)
LLVM_CONFIG ?= $(shell which llvm-config 2>/dev/null)
LLVM_AS ?= $(shell which llvm-as 2>/dev/null)
LLVM_DIS ?= $(shell which llvm-dis 2>/dev/null)
LLC ?= $(shell which llc 2>/dev/null)

ifeq ($(CLANG),)
  $(error Not found clang, please install clang first)
endif
ifeq ($(LLVM_CONFIG),)
  $(error Not found llvm-config, please install llvm first)
endif

LLVM_CFLAGS += $(shell ${LLVM_CONFIG} --cflags)
LLVM_CXXFLAGS += $(shell ${LLVM_CONFIG} --cxxflags)

LLVM_LDFLAGS += $(shell ${LLVM_CONFIG} --ldflags)


%.ll: %.c
	@echo -e "  CLANG LL  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -S -emit-llvm $(<) -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.bc: %.ll
	@echo -e "  LLVM AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(LLVM_AS) $(<) -o $(@)

%.dis.ll: %.bc
	@echo -e "  LLVM DIS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(LLVM_DIS) $(<) -o $(@)

%.ll.s: %.ll
	@echo -e "  LLC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(LLC) $(<) -o $(@)
