# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - BPF_SUPPORT_FENTRY=[y|n]
#
ifndef _BPF_FENTRY_MK
_BPF_FENTRY_MK = 1

include bpf/bpf.mk
include bpf/bpftool.mk
include kernel.mk

# TODO: Got be a better way.
BPF_SUPPORT_FENTRY := $(call kver_gt,5,5,0)

ifdef DEBUG
  $(info BPF_SUPPORT_FENTRY = ${BPF_SUPPORT_FENTRY})
endif

endif
