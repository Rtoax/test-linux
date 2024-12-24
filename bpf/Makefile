# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../scripts/logos.mk

sub-dir := bcc
sub-dir += bpftrace
sub-dir += bpftool
sub-dir += btf
sub-dir += c
sub-dir += libbpf
sub-dir += samples
sub-dir += seccomp
sub-dir += usdt

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)
	$(Q)./tcpdump.sh
	$(call tl_ascii_logo_ebpf_bee_summit_2021)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
