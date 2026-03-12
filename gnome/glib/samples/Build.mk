# SPDX-License-Identifier: GPL-3.0
include glib.mk

target-y += gthread
target-y += size

CFLAGS += $(GLIB_CFLAGS)
LDFLAGS += $(GLIB_LDFLAGS)
