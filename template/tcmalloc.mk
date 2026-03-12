# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_TCMALLOC=[y|n]
# - tcmalloc-cflags=
# - tcmalloc-ldflags=
#
ifndef _TCMALLOC_MK
_TCMALLOC_MK = 1

TCMALLOC_H := /usr/include/gperftools/tcmalloc.h
tcmalloc-cflags :=
tcmalloc-ldflags :=

ifneq ($(wildcard $(TCMALLOC_H)),)
  tcmalloc-cflags += -DHAVE_TCMALLOC=1
  tcmalloc-ldflags += -ltcmalloc
  tcmalloc-ldflags += -ltcmalloc_and_profiler
  tcmalloc-ldflags += -ltcmalloc_debug
  tcmalloc-ldflags += -ltcmalloc_minimal
  tcmalloc-ldflags += -ltcmalloc_minimal_debug
  export HAVE_TCMALLOC := y
else
  $(warning "WARNING: You need to install tcmalloc")
  export HAVE_TCMALLOC := n
endif

endif
