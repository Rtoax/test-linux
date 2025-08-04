# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

LIBCGROUP_HDR := /usr/include/libcgroup.h

ifneq ($(wildcard $(LIBCGROUP_HDR)),)
  CFLAGS += -DHAVE_LIBCGROUP
  LDFLAGS += -lcgroup
else
  $(warning "WARNING: You need to install libcgroup")
endif
