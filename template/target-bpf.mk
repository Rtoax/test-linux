# SPDX-License-Identifier: GPL-3.0
CLANG ?= $(shell which clang 2>/dev/null)
ifeq ($(CLANG),)
  $(error Not found clang, please install clang first)
endif

include ${TEMPLATE_DIR}/../bpf/bpf.mk

CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

%.bpf.o: %.bpf.c
	@echo -e "  CLANG BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))
