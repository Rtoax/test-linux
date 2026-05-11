# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - GDB=[/usr/bin/gdb]
# - HAVE_GDB=[y|n]
#
ifndef _GDB_MK
_GDB_MK = 1

include define.mk

$(call find_cmd_and_def,gdb)

endif
