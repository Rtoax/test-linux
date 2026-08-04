# See https://git.sr.ht/~brianwitte/gcc-bpf-example
#   - github fork: https://github.com/Rtoax/gcc-bpf-example
#   - gitee fork: https://gitee.com/rtoax/gcc-bpf-example
# TODO: move to template/

include bpf/bpf.mk
include bpf/gcc.mk

CFLAGS_GCC_BPF += ${bpf-cflags}
CFLAGS_GCC_BPF += -g -gbtf -Wall -O2
CFLAGS_GCC_BPF += -Wno-error=attributes -Wno-error=address-of-packed-member
CFLAGS_GCC_BPF += -Wno-compare-distinct-pointer-types

# is target-bpf-y
${OUTPUT}%.bpf.gcc.o: %.bpf.c | ${OUTPUT}
	@$(call log_obj,GCC BPF,$(@))
	${Q}$(BPF_GCC) -MMD -MT $(@) -MF $(@:=.d) -c $(<) -o $(@) ${CFLAGS_GCC_BPF} $(CFLAGS_GCC_BPF_$(*))
