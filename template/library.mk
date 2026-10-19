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
_LIBRARY_MK = 1

include os.mk

LDCONFIG := $(shell which ldconfig 2>/dev/null || true)
ifeq ($(LDCONFIG),)
  ifneq ($(wildcard /sbin/ldconfig),)
    LDCONFIG := /sbin/ldconfig
  endif
endif

ifeq ($(call is_os, alpine), y)
# alpine ldconfig (musl libc) could not get library list.
lib_list_cmd = find /usr/lib
else
lib_list_cmd = ${LDCONFIG} -p
endif

# $1: library name, like libc.so
define find_library_path
$(shell ${lib_list_cmd} | grep -w "${1}" | awk '{printf $$NF"\n"}' | head -1)
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

ifdef TEST
  rslt = $(call find_library_path,libabcdefg.so)
  ifneq ($(rslt),)
    $(error find_library_path test failed, got ${rslt})
  endif

  rslt = $(call have_library,libc.so)
  rslt2 = $(call have_library,libabcdefg.so)
  ifneq (${rslt}${rslt2},yn)
    $(error have_library test failed, need yn, but got ${rslt}${rslt2})
  endif
endif

endif
