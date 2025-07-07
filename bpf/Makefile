# SPDX-License-Identifier: GPL-3.0
include ../scripts/ansi.mk
include bpf.mk

sub-dir := bcc
sub-dir += bpftrace
sub-dir += bpftool
sub-dir += btf
sub-dir += c
sub-dir += libbpf
sub-dir += samples
sub-dir += seccomp
sub-dir += usdt
sub-dir += xdp

TARGETS_SHELL := tcpdump.sh
TARGETS_BPF := tcpdump.bpf.o

TARGETS_POST := post0
TARGETS_POST += $(patsubst %.bpf.o,%.bpf.disasm,$(TARGETS_BPF))

include ../template/main.mk

tcpdump.bpf.o: vmlinux.h

post0:
	$(Q)./tcpdump.sh
	$(call tl_ascii_logo_ebpf_bee_summit_2021)
