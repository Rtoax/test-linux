# SPDX-License-Identifier: GPL-3.0
#
# Output definitions
# - LDCONFIG=
#
# Functions:
# - find_library_path($name)=/path/to/$name
# - have_library($name)=[y|n]
#
ifndef _LDCONFIG_MK
_LDCONFIG_MK = 1

LDCONFIG := $(shell which ldconfig 2>/dev/null || true)
ifeq ($(LDCONFIG),)
  ifneq ($(wildcard /sbin/ldconfig),)
    LDCONFIG := /sbin/ldconfig
  endif
endif

# $1: library name, like libc.so
define find_library_path
$(shell ${LDCONFIG} -p | grep -w "${1}" | awk '{printf $$NF"\n"}' | head -1)
endef

# $1: library name, like libc.so
define have_library
$(if $(call find_library_path,${1}),$(shell echo y),$(shell echo n))
endef

ifdef DEBUG
  $(info LDCONFIG = ${LDCONFIG})
  $(info find_library_path(libc.so) = $(call find_library_path,libc.so))
endif

ifeq ($(LDCONFIG),)
  $(error "Not found ldconfig in anywhere, install first")
endif
ifneq ($(call have_library,libc.so)$(call have_library,libabcdefg),yn)
  $(error have_library test failed)
endif

endif
