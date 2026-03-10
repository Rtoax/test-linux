# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
#
ifndef _GLIB_MK
_GLIB_MK = 1

GLIB_VERSION := glib-2.0
GLIB_CFLAGS := $(shell pkg-config --cflags ${GLIB_VERSION})
GLIB_LDFLAGS := $(shell pkg-config --libs ${GLIB_VERSION})

ifdef DEBUG
  $(info GLIB_CFLAGS = $(GLIB_CFLAGS))
  $(info GLIB_LDFLAGS = $(GLIB_LDFLAGS))
endif

export GLIB_CFLAGS GLIB_LDFLAGS

endif
