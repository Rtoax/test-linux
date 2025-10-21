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
