# SPDX-License-Identifier: GPL-3.0
include ../template/ansi.mk
include bpf.mk

sub-dir := bcc
sub-dir += bpftrace
sub-dir += bpftool
sub-dir += btf
sub-dir += c
sub-dir += jit
sub-dir += libbpf
sub-dir += samples
sub-dir += seccomp
sub-dir += usdt
sub-dir += xdp

targets := tcpdump
targets-shell := tcpdump.sh
targets-bpf := tcpdump.bpf.o

targets-post := post0
targets-post += $(patsubst %.bpf.o,%.bpf.disasm,$(targets-bpf))

CFLAGS_BPF_tcpdump := -DVERIFER=1

include ../template/main.mk

tcpdump: tcpdump.o
tcpdump.bpf.o: vmlinux.h

post0:
	$(Q)./tcpdump.sh
	$(call bpf_logo_summit_2021)
