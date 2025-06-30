# SPDX-License-Identifier: GPL-3.0
CLANG ?= $(shell which clang 2>/dev/null)
ifeq ($(CLANG),)
  $(error Not found clang, please install clang first)
endif

PAHOLE := $(shell which pahole 2>/dev/null || true)
ifeq ($(PAHOLE),)
  $(error Not found pahole, please install dwarves)
endif

include ${TEMPLATE_DIR}/../bpf/bpf.mk

CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

%.bpf.o: %.bpf.c
	$(call log_tgt_obj,BPF,$(<),$(@))
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

%.bpf.s: %.bpf.c
	$(call log_tgt_obj,BPF S,$(<),$(@))
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

%.bpf.btf: %.bpf.o
	$(call log_tgt_obj,BTF,$(<),$(@))
	${Q}$(PAHOLE) -JV $(<) > $(@)
