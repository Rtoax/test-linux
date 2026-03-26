# SPDX-License-Identifier: GPL-3.0
#
# Output definitions
# - LDCONFIG=
#
ifndef _LDCONFIG_MK
_LDCONFIG_MK = 1

LDCONFIG := $(shell which ldconfig 2>/dev/null || true)
ifeq ($(LDCONFIG),)
  ifneq ($(wildcard /sbin/ldconfig),)
    LDCONFIG := /sbin/ldconfig
  endif
endif

ifdef DEBUG
  $(info LDCONFIG = ${LDCONFIG})
endif

ifeq ($(LDCONFIG),)
  $(error "Not found ldconfig in anywhere, install first")
endif

endif
