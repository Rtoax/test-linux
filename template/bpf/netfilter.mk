# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - SUPPORT_BPF_PROG_TYPE_NETFILTER=[y|n]
#
ifndef _BPF_NETFILTER_MK
_BPF_NETFILTER_MK = 1

include bpf/bpf.mk
include bpf/bpftool.mk
include kernel.mk

# linux v6.3-rc6-1646-gfd9c663b9ad6
# commit fd9c663b9ad6 ("bpf: minimal support for programs hooked into netfilter framework")
# TODO: Got be a better way.
SUPPORT_BPF_PROG_TYPE_NETFILTER := $(call kver_gt,6,3,0)

ifdef DEBUG
  $(info SUPPORT_BPF_PROG_TYPE_NETFILTER = ${SUPPORT_BPF_PROG_TYPE_NETFILTER})
endif

endif
