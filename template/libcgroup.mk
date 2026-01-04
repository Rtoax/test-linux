# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
_LIBCGROUP_MK = 1

LIBCGROUP_HDR := /usr/include/libcgroup.h

ifneq ($(wildcard $(LIBCGROUP_HDR)),)
  ifdef STATIC
    $(warning "WARNING: libcgroup not support STATIC yet!!!")
  else
    CFLAGS += -DHAVE_LIBCGROUP=1
    LDFLAGS += -lcgroup
  endif
else
  $(warning "WARNING: You need to install libcgroup")
endif
