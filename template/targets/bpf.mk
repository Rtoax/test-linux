# SPDX-License-Identifier: GPL-3.0
_TARGET_BPF = 1

CLANG := $(shell which clang 2>/dev/null)
LLVM_OBJDUMP := $(shell which llvm-objdump 2>/dev/null)
VMLINUX_H := vmlinux.h
BPFTOOL := bpftool

ifeq ($(CLANG),)
  $(error Not found clang, please install clang first)
endif

ifeq ($(LLVM_OBJDUMP),)
  $(error Not found llvm-objdump, please install llvm first)
endif

include ${TEMPLATE_DIR}/../pahole/pahole.mk
include ${TEMPLATE_DIR}/../bpf/bpf.mk
include ${TEMPLATE_DIR}/../bpf/bpftool/bpftool.mk
include ${TEMPLATE_DIR}/../bpf/btf/btf.mk

OBJDUMP_ARGS :=

CFLAGS_BPF += -I.
CFLAGS_BPF += -O2 -g
# Like -target bpfel
CFLAGS_BPF += -target bpf -mlittle-endian
CFLAGS_BPF += -mcpu=v3
# FIXME: vmlinux.h use macro 'restrict'
# TODO: linux selftests/bpf is -std=gnu11
CFLAGS_BPF += -std=gnu89 -Drestrict=
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

ifdef DEBUG
  CFLAGS_BPF += -DDEBUG=${DEBUG}
  $(info CFLAGS_BPF := ${CFLAGS_BPF})
endif

${OUTPUT}%.bpf.o: %.bpf.c | ${OUTPUT}
	$(call log_tgt_obj,BPF,$(<),$(@))
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

${OUTPUT}%.bpf.disasm: ${OUTPUT}%.bpf.o | ${OUTPUT}
	$(call log_tgt_obj,BPF DIS,$(<),$(@))
	${Q}${LLVM_OBJDUMP} --disassemble --source ${OBJDUMP_ARGS} $(<) > $(@)

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

#$(targets-bpf): %:
#	$(call log_tgt_exe,LD BPF,$(<),$(@))
#	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${VMLINUX_H}: | ${OUTPUT}
	$(call log_tgt_obj,BTF_H,,$(@))
	$(call bpf_gen_vmlinux_h,${VMLINUX_H})
