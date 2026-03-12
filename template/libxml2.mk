# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_LIBXML2=[y|n]
#
ifndef _LIBXML2_MK
_LIBXML2_MK = 1

LIBXML2_VERSION := libxml-2.0
LIBXML2_LIBS := $(shell pkg-config --libs libxml-2.0)
LIBXML2_CFLAGS := $(shell pkg-config --cflags libxml-2.0)

endif # end of _LIBXML2_MK
