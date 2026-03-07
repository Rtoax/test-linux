# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Input definitions:
# - PIE=1
# - NOPIE=1
#
# Output definitions:
# - CFLAGS_PIE=
# - LDFLAGS_PIE=
#
# Append definitions:
# - MAKEFLAGS+=
#
ifndef _PIE_MK
export _PIE_MK = 1

CFLAGS_PIE :=
LDFLAGS_PIE :=

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifdef PIE
  # clang: not support -pie in cflags
  ifeq ($(CC),gcc)
    CFLAGS_PIE += -pie
  endif
  CFLAGS_PIE += -fPIE
  LDFLAGS_PIE += -pie -fPIE
  MAKEFLAGS += PIE=1
endif

ifdef NOPIE
  CFLAGS_PIE += -no-pie
  LDFLAGS_PIE += -no-pie
  MAKEFLAGS += NOPIE=1
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif

ifdef DEBUG
  $(info CFLAGS_PIE = ${CFLAGS_PIE})
  $(info LDFLAGS_PIE = ${LDFLAGS_PIE})
endif

export CFLAGS_PIE LDFLAGS_PIE

endif
