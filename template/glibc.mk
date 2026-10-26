# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Output definitions:
# - USE_GNU_LIBC=[y|n]
# - GLIBC_VERSION=
# - LIBC_SO_PATH=
#
# Functions:
# - glibc_{gt,ge,eq,lt,le}(major, minor)=[y|n]
# - glibc_probe_printf()
# - glibc_sym_addr()
#
ifndef _GLIBC_MK
_GLIBC_MK = 1

include dir.mk
include library.mk
include version.mk

ifeq ($(shell ldd --version 2>&1 | grep -owi -e gnu -e glibc),)
  export USE_GNU_LIBC := n
else

export USE_GNU_LIBC := y

glibc_mk_cachefile := ${TOPDIR}/template/.glibc.mk.cache
glibc_mk_origfile := ${TOPDIR}/template/glibc.mk
ifeq ($(call is_newer,${glibc_mk_cachefile},${glibc_mk_origfile}),y)
  include ${glibc_mk_cachefile}
else

include bits/mk-cache.mk

$(call mkcache_generate,${glibc_mk_cachefile})

glibcversh = ${TOPDIR}/scripts/version/glibc.sh

GLIBC_VERSION := $(shell ${glibcversh})
GLIBC_MAJOR := $(shell ${glibcversh} --major)
GLIBC_MINOR := $(shell ${glibcversh} --minor)

$(call mkcache_append,GLIBC_VERSION,${glibc_mk_cachefile})
$(call mkcache_append,GLIBC_MAJOR,${glibc_mk_cachefile})
$(call mkcache_append,GLIBC_MINOR,${glibc_mk_cachefile})

endif # end of cache

$(eval $(call define_version,glibc,version2_code1616,y,${GLIBC_MAJOR},${GLIBC_MINOR}))

# Get libc.so.6 abs-path
LIBC_SO_PATH := $(call find_library_path,libc.so.6)

# Probe printf(3) with non-output glibc command
LIBC_PRINTF_PROBE := '\#include <stdio.h>\n'
LIBC_PRINTF_PROBE += 'int main(void) {\n'
LIBC_PRINTF_PROBE += '	printf("hello\\n");\n'
LIBC_PRINTF_PROBE += '}'

define glibc_probe_printf
  $(shell printf '%b\n' $(LIBC_PRINTF_PROBE) | \
    $(CC) -x c -Wall - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

# Get symbol address from libc.so.6, readelf output format
#
# 2611: 0000000000035a80   204 FUNC    GLOBAL DEFAULT    3 printf@@GLIBC_2.2.5
#
# $1 - symbol
define glibc_sym_addr
$(shell readelf --syms --wide ${LIBC_SO_PATH} \
		| grep -w $(1) | grep -e GLOBAL -e LOCAL | head -1 \
		| awk '{printf "0x"$$2}')
endef

ifdef DEBUG
  $(info USE_GNU_LIBC = ${USE_GNU_LIBC})
  $(info GLIBC_VERSION = ${GLIBC_VERSION})
  $(info GLIBC_MAJOR = ${GLIBC_MAJOR})
  $(info GLIBC_MINOR = ${GLIBC_MINOR})
  $(info LIBC_SO_PATH = ${LIBC_SO_PATH})
  $(info printf = <$(call glibc_sym_addr,printf)>)
endif

export GLIBC_VERSION GLIBC_MAJOR GLIBC_MINOR
export LIBC_SO_PATH

endif # end of USE_GNU_LIBC
endif # end of _GLIBC_MK
