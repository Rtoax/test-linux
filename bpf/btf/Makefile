# SPDX-License-Identifier: GPL-3.0
include btf.mk

sub-dir := examples

ifneq ($(call vmlinux_has_struct,task_struct),y)
  $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_struct,task_struct)>)
endif
ifneq ($(call vmlinux_has_sym,task_struct),y)
  $(error Not found task_struct in vmlinux.h: <$(call vmlinux_has_sym,task_struct)>)
endif

TARGETS_PREP := vmlinux.h

include ../../template/main.mk

include ../bpftool/vmlinux.h.mk
