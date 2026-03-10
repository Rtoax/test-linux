# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBSECCOMP=[y|n]
# - libseccomp-cflags=
# - libseccomp-ldflags=
#
ifndef _LIBSECCOMP_MK
_LIBSECCOMP_MK = 1

LIBSECCOMP_H := /usr/include/seccomp.h
libseccomp-cflags :=
libseccomp-ldflags :=

ifneq ($(wildcard $(LIBSECCOMP_H)),)
  ifdef STATIC
    $(warning "WARNING: libseccomp not support STATIC yet!!!")
  else
    libseccomp-cflags += -DHAVE_LIBSECCOMP=1
    libseccomp-ldflags += -lseccomp
  endif
  export HAVE_LIBSECCOMP := y
else
  $(warning "WARNING: You need to install libseccomp")
  export HAVE_LIBSECCOMP := n
endif

endif
