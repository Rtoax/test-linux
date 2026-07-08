# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_BPF_MK
_TARGET_BPF_MK = 1

include llvm.mk
include pahole.mk
include bpf/bpf.mk
include bpf/btf.mk
include bpf/bpftool.mk
include bpf/helper.mk
include cflags.mk

CFLAGS_BPF += -I.
CFLAGS_BPF += -I${OUTPUT}
CFLAGS_BPF += -O2 -g
# Like -target bpfel
CFLAGS_BPF += -target bpf -mlittle-endian
CFLAGS_BPF += -mcpu=v3
# FIXME: vmlinux.h use macro 'restrict'
# TODO: linux selftests/bpf is -std=gnu11
CFLAGS_BPF += -std=gnu89 -Drestrict=
CFLAGS_BPF += -DCONFIG_UID=${CONFIG_UID}
CFLAGS_BPF += $(bpf-cflags)
CFLAGS_BPF += ${bpf-helper-cflags}
CFLAGS_BPF += -Wno-missing-declarations

ifdef DEBUG
  CFLAGS_BPF += -DDEBUG=${DEBUG}
  # Or, it can be divided into two steps:
  # $ clang -O2 -g -target bpf -emit-llvm -c a.c -o a.bc
  # $ llc a.bc -march=bpf -mattr=dwarfris -filetype=obj -o a.o
  CFLAGS_BPF += -g -Xclang -target-feature -Xclang +dwarfris
  $(info CFLAGS_BPF = ${CFLAGS_BPF})
endif

# Note: This is target-bpf-y
# Compile .bpf.o methods:
# 1. $ clang -O2 -target bpf -c $(<) -S -o $(<:.c=.S)
#    $ llvm-mc -triple bpf -filetype=obj -o $(@) $(<:.c=.S)
# 2. $ clang -O2 -target bpf -emit-llvm -c $(<) -o $(<:.c=.bc)
#    $ llc $(<:.c=.bc) -march=bpf -filetype=obj -o $(@)
${OUTPUT}%.bpf.o: %.bpf.c | ${OUTPUT}
	$(call log_obj,${CLANG} BPF,$(@))
	${Q}$(CLANG) -MMD -MT $(@) -MF $(@:=.d) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

# LLVM IR bitcode, only add -emit-llvm
${OUTPUT}%.bpf.bc: %.bpf.c | ${OUTPUT}
	$(call log_obj,${CLANG} BPF,$(@))
	${Q}$(CLANG) -MMD -MT $(@) -MF $(@:=.d) -emit-llvm -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

# Other arguments:
# --no-show-raw-insn
${OUTPUT}%.bpf.disasm: ${OUTPUT}%.bpf.o | ${OUTPUT}
	$(call log_obj,${LLVM_OBJDUMP} BPF DIS,$(@))
	${Q}${LLVM_OBJDUMP} --disassemble --source $(<) > $(@)

${OUTPUT}%.bpf.s: %.bpf.c | ${OUTPUT}
	$(call log_obj,${CLANG} BPF S,$(@))
	${Q}$(CLANG) -S $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

${OUTPUT}%.skel.h: ${OUTPUT}%.bpf.o | ${OUTPUT}
	$(call log_obj,${BPFTOOL} SKEL,$(@))
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
	$(call log_obj,${PAHOLE} BTF,$(@))
	${Q}$(PAHOLE) -JV $(<) > $(@)

${target-btf-y}: | ${OUTPUT}
	$(call log_tgt,BTF_H,$(@))
	$(call btf_gen_hdr,$(@:.h=),$(@))

# Special btf header, this may duplicate of target-btf-y.
${VMLINUX_H}: | ${OUTPUT}
	$(call log_tgt,BTF_H,$(@))
	$(call btf_gen_hdr,vmlinux,${VMLINUX_H})

# Include all the .bpf.o.d depends files
$(foreach dep, $(shell ls ${OUTPUT}*.bpf.o.d 2>/dev/null), \
  $(if $(shell test -f ${dep} && echo yes), \
    $(if ${DEBUG}, $(info Found ${dep})) \
    $(eval include ${dep}), \
    $(if ${DEBUG}, $(info Not found ${dep})) \
  ) \
)

endif
