# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_JEMALLOC=[y|n]
# - libjemalloc-cflags=
# - libjemalloc-ldflags=
#
ifndef _JEMALLOC_MK
_JEMALLOC_MK = 1

JEMALLOC_H := /usr/include/jemalloc.h
libjemalloc-cflags :=
libjemalloc-ldflags :=

ifneq ($(wildcard $(JEMALLOC_H)),)
  libjemalloc-cflags += -DHAVE_JEMALLOC=1
  libjemalloc-ldflags += -ljemalloc
  export HAVE_JEMALLOC := y
else
  $(warning "WARNING: You need to install jemalloc")
  export HAVE_JEMALLOC := n
endif

endif
