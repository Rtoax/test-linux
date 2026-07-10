# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - SUPPORT_BPF_MAP_TYPE_ARENA=[y|n]
#
ifndef _BPF_MAP_MK
_BPF_MAP_MK = 1

include kernel.mk

# linux v6.8-rc6-1938-g317460317a02 >= v6.9
# commit 317460317a02 ("bpf: Introduce bpf_arena.")
SUPPORT_BPF_MAP_TYPE_ARENA := $(call kver_gt,6,8,0)

ifdef DEBUG
  $(info SUPPORT_BPF_MAP_TYPE_ARENA = ${SUPPORT_BPF_MAP_TYPE_ARENA})
endif

endif
