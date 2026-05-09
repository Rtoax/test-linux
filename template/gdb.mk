# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_GDB=[y|n]
#
ifndef _GDB_MK
_GDB_MK = 1

GDB := $(shell which gdb 2>/dev/null)
ifeq ($(wildcard ${GDB}),)
  HAVE_GDB := n
else
  HAVE_GDB := y
endif

ifdef DEBUG
  $(info GDB = ${GDB})
  $(info HAVE_GDB = ${HAVE_GDB})
endif

export GDB
export HAVE_GDB

endif
