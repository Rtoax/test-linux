# SPDX-License-Identifier: GPL-3.0
SHELL = bash

include ../scripts/tlbuild.mk

sub-dir := bcc
sub-dir += bpftrace
sub-dir += c
sub-dir += samples
sub-dir += seccomp
sub-dir += usdt

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)
	$(call tl_ascii_logo_ebpf_bee)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
