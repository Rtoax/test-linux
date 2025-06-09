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

TARGETS_POST := post0

include ../template/main.mk

post0:
	$(Q)./tcpdump.sh
	$(call tl_ascii_logo_ebpf_bee_summit_2021)
