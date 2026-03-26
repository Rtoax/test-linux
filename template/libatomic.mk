# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBATOMIC=y

ifndef _LIBATOMIC_MK
_LIBATOMIC_MK = 1

include ldconfig.mk

LIBATOMIC := $(shell ${LDCONFIG} -p | grep -w libatomic.so 2>/dev/null | awk '{print $$4}')

ifneq ($(LIBATOMIC),)
  HAVE_LIBATOMIC := y
  export HAVE_LIBATOMIC
else
  $(warning "WARNING: You need to install libatomic")
endif

endif
