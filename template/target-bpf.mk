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
include ${TEMPLATE_DIR}/../bpf/bpftool/bpftool.mk

CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

${OUTPUT}%.bpf.o: %.bpf.c | ${OUTPUT}
	$(call log_tgt_obj,BPF,$(<),$(@))
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

${OUTPUT}%.bpf.s: %.bpf.c | ${OUTPUT}
	$(call log_tgt_obj,BPF S,$(<),$(@))
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

${OUTPUT}%.skel.h: ${OUTPUT}%.bpf.o | ${OUTPUT}
	$(call log_tgt_obj,SKEL,$(<),$(@))
	${Q}$(BPFTOOL) gen object $(<:.o=.linked1.o) $(<)
	${Q}$(BPFTOOL) gen object $(<:.o=.linked2.o) $(<:.o=.linked1.o)
	${Q}$(BPFTOOL) gen object $(<:.o=.linked3.o) $(<:.o=.linked2.o)
	${Q}diff $(<:.o=.linked2.o) $(<:.o=.linked3.o)
	${Q}$(BPFTOOL) gen skeleton $(SKEL_ARGS) $(SKEL_ARGS_$(*)) \
		$(<:.o=.linked3.o) name $(subst -,_,$(notdir $(<:.bpf.o=)))_bpf > $@ || rm -f $@
	# FIXME: old bpftool not support 'gen subskeleton' command.
	# bpftool commit ad805235e295 ("bpftool: Add support for subskeletons")
	# https://github.com/libbpf/bpftool.git
	#${Q}$(BPFTOOL) gen subskeleton \
	#	$(<:.o=.linked3.o) name $(subst -,_,$(notdir $(<:.bpf.o=)))_bpf > $(@:.skel.h=.subskel.h)

${OUTPUT}%.bpf.btf: ${OUTPUT}%.bpf.o | ${OUTPUT}
	$(call log_tgt_obj,BTF,$(<),$(@))
	${Q}$(PAHOLE) -JV $(<) > $(@)

#$(TARGETS_BPF): %:
#	$(call log_tgt_exe,LD BPF,$(<),$(@))
#	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))
