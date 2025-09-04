# SPDX-License-Identifier: GPL-3.0
include ../compiler/compiler.mk
include ../glibc/glibc.mk
include ../template/ansi.mk
include ../template/dir.mk
include ../template/git.mk
include ../template/success.mk
include ../template/wow.mk
include ../template/logo.mk
include ../template/cpu.mk
include ../template/os.mk
include ../gnu/gnu.mk
include ../bpf/bpf.mk

targets-prep := test_call
targets-shell := moonlight.sh
targets-shell += gotoxy.sh
targets-shell += termplot.sh
targets-shell += kconfig_compare.sh
targets-shell += patchset_examples.sh

SHELL_ARGS_kconfig_compare.sh := --base ../kconfig --config ../kconfig --display all

include ../template/main.mk

test_call:
	$(call success)
	$(call wow)
	$(call wow,PREFIX)
	$(call tl_logo1,===)
	$(call bpf_logo_summit_2021)
	$(call gnu_logo)
	$(call git_config)
	$(call git_archive)
