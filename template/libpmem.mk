# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBPMEM=[y|n]
# - libpmem-cflags=
# - libpmem-ldflags=
#
ifndef _LIBPMEM_MK
_LIBPMEM_MK = 1

LIBPMEM_H := /usr/include/libpmem.h
libpmem-cflags :=
libpmem-ldflags :=

ifneq ($(wildcard $(LIBPMEM_H)),)
  ifdef STATIC
    $(warning "WARNING: libpmem not support STATIC yet!!!")
  else
    libpmem-cflags += -DHAVE_LIBPMEM=1
    libpmem-ldflags += -lpmem
  endif
  export HAVE_LIBPMEM := y
else
  $(warning "WARNING: You need to install libpmem")
  export HAVE_LIBPMEM := n
endif

endif
