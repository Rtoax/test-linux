# SPDX-License-Identifier: GPL-3.0
include ../template/ansi.mk
include bpf.mk
include logo.mk

subdir-y := bcc
subdir-y += bpftrace
subdir-y += bpftool
subdir-y += btf
subdir-y += c
subdir-y += jit
subdir-y += libbpf
subdir-y += samples
subdir-y += seccomp
subdir-y += usdt
subdir-y += xdp

target-y := tcpdump
target-shell-y := tcpdump.sh
target-bpf-y := tcpdump.bpf.o

target-post-y := post0
target-post-y += $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))

CFLAGS_BPF_tcpdump := -DVERIFER=1

include ../template/main.mk

tcpdump: tcpdump.o
tcpdump.bpf.o: vmlinux.h

post0:
	$(Q)./tcpdump.sh
	$(call bpf_logo_summit_2021)
