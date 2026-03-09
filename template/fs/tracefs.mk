# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - TRACEFS=[/sys/kernel/tracing/,/sys/kernel/debug/tracing/]
#
ifndef _FS_TRACEFS_MK
_FS_TRACEFS_MK = 1

PATH_TRACEFS := /sys/kernel/tracing/

ifdef DEBUG
  $(info PATH_TRACEFS = ${PATH_TRACEFS})
endif

endif
