# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

CC := gcc
include ../compiler/compiler.mk
include ../tlbuild.mk
include ../glibc/glibc.mk
include success.mk
include wow.mk
include ansi.mk
include logo.mk
include ../gnu/gnu.mk
include git.mk
include ../bpf/bpf.mk

all: test_call

test_call:
	$(call success)
	$(call wow)
	$(call wow,PREFIX)
	$(call tl_ascii_logo1,===)
	$(call tl_ascii_logo_ebpf_bee_summit_2021)
	$(call tl_ascii_logo_gnu)
	$(call git_config)
	$(call git_archive)
	$(Q)./moonlight.sh
	$(Q)./gotoxy.sh
	@echo -e "  \033[1;33mDone\033[m"
test:

clean:
	@rm -f test-linux-*.tar.gz
