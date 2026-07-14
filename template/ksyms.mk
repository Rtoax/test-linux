# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - KALLSYMS=[/proc/kallsyms]
#
# Functions:
#
ifndef _KERNEL_MK
_KERNEL_MK = 1

include shell.mk
include sudo.mk

KALLSYMS := /proc/kallsyms


ifdef DEBUG
  $(info KALLSYMS = ${KALLSYMS})
endif

endif
