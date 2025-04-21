# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
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

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	$(Q)./tcpdump.sh
	$(call tl_ascii_logo_ebpf_bee_summit_2021)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
