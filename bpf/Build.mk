# SPDX-License-Identifier: GPL-3.0
include bpf/bpf.mk
include bpf/logo.mk
include kconfig.mk

subdir-y := bcc
subdir-y += blazesym
subdir-y += bpftrace
subdir-y += bpftool
subdir-y += btf
subdir-y += c
subdir-y += cilium
subdir-y += insn
subdir-y += kfunc
subdir-y += jit
subdir-y += libbpf
subdir-y += samples
subdir-y += seccomp
subdir-$(CONFIG_SCHED_CLASS_EXT) += sched_ext
subdir-y += usdt
subdir-y += xdp

target-y := tcpdump
shell-y := tcpdump.sh
target-bpf-y := ${OUTPUT}tcpdump.bpf.o

target-post-y := post0
target-post-y += $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))

CFLAGS_BPF_tcpdump := -DVERIFER=1
