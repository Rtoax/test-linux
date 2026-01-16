# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Ouput definitions:
# - CPU_VENDOR_ID=[GenuineIntel|AuthenticAMD|ARM|HiSilicon|Phytium]
# - cpu-cflags=
#
ifndef _CPU_MK
_CPU_MK = 1

include bits/cpu-cache.mk
include bits/cpu-feature.mk

CPU_VENDOR_ID := $(shell lscpu | grep ^Vendor | awk '{print $$3}')

ifdef DEBUG
  $(info cpu-cflags = ${cpu-cflags})
  $(info CPU_VENDOR_ID = ${CPU_VENDOR_ID})
endif

export cpu-cflags
export CPU_VENDOR_ID

endif
