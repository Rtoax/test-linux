# SPDX-License-Identifier: GPL-3.0
#
# Output definitions
# - LDCONFIG=
#
ifndef _LDCONFIG_MK
export _LDCONFIG_MK = 1

LDCONFIG := $(shell which ldconfig 2>/dev/null || true)
ifeq ($(LDCONFIG),)
  ifneq ($(wildcard /sbin/ldconfig),)
    LDCONFIG := /sbin/ldconfig
  else
    $(error "Not found bpftool in anywhere, install first")
  endif
endif


endif
