# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBCGROUP=[y|n]
# - libcgroup-cflags=
# - libcgroup-ldflags=
#
ifndef _LIBCGROUP_MK
export _LIBCGROUP_MK = 1

LIBCGROUP_H := /usr/include/libcgroup.h
libcgroup-cflags :=
libcgroup-ldflags :=

ifneq ($(wildcard $(LIBCGROUP_H)),)
  ifdef STATIC
    $(warning "WARNING: libcgroup not support STATIC yet!!!")
  else
    libcgroup-cflags += -DHAVE_LIBCGROUP=1
    libcgroup-ldflags += -lcgroup
  endif
  export HAVE_LIBCGROUP := y
else
  $(warning "WARNING: You need to install libcgroup")
  export HAVE_LIBCGROUP := n
endif

endif
