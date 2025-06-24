# SPDX-License-Identifier: GPL-3.0
CC := gcc
include ../compiler/compiler.mk
include ../glibc/glibc.mk
include success.mk
include wow.mk
include ansi.mk
include logo.mk
include ../gnu/gnu.mk
include git.mk
include ../bpf/bpf.mk
include ascii.mk

TARGETS_PREP := test_call
TARGETS_SHELL := moonlight.sh
TARGETS_SHELL += gotoxy.sh
TARGETS_SHELL += kconfig_compare.sh
TARGETS_SHELL += patchset_examples.sh

SHELL_ARGS_kconfig_compare.sh := --base ../kconfig --config ../kconfig --display all

include ../template/main.mk

test_call:
	$(call success)
	$(call wow)
	$(call wow,PREFIX)
	$(call tl_ascii_logo1,===)
	$(call tl_ascii_logo_ebpf_bee_summit_2021)
	$(call tl_ascii_logo_gnu)
	$(call git_config)
	$(call git_archive)
