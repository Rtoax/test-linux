# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBATOMIC=y

_LIBATOMIC_MK = 1

LIBATOMIC := $(shell ldconfig -p | grep -w libatomic.so 2>/dev/null | awk '{print $$4}')

ifneq ($(LIBATOMIC),)
  HAVE_LIBATOMIC := y
  export HAVE_LIBATOMIC
else
  $(warning "WARNING: You need to install libatomic")
endif
