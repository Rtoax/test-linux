# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2026 Rong Tao. All rights reserved.
#
# Definitions:
# - LD_BFD=[/usr/bin/ld.bfd]
# - HAVE_LD_BFD=[y|n]
# - BINUTILS_VERSION=
# - BINUTILS_MAJOR=
# - BINUTILS_MINOR=
# - binutils-cflags=
#
# Functions:
# - binutils_{gt,ge,eq,lt,le}(major, minor)=[y|n]
#
ifndef _BINUTILS_MK
_BINUTILS_MK = 1

include dir.mk
include define.mk
include version.mk

binutils-cflags :=

$(call find_cmd_and_def,ld.bfd)

ifeq ($(LD_BFD),)
  $(warning "Not found linker ld.bfd, install binutils first")
endif

binutils_mk_cachefile := ${TOPDIR}/template/.binutils.mk.cache
binutils_mk_origfile := ${TOPDIR}/template/binutils.mk
ifeq ($(call is_newer,${binutils_mk_cachefile},${binutils_mk_origfile}),y)
  include ${binutils_mk_cachefile}
else

include bits/mk-cache.mk

$(call mkcache_generate,${binutils_mk_cachefile})

binutilsversh = ${TOPDIR}/scripts/version/binutils.sh

# Get binutils version
BINUTILS_VERSION := $(shell ${binutilsversh})
BINUTILS_MAJOR := $(shell ${binutilsversh} --major)
BINUTILS_MINOR := $(shell ${binutilsversh} --minor)

binutils-cflags += -DBINUTILS_MAJOR=${BINUTILS_MAJOR}
binutils-cflags += -DBINUTILS_MINOR=${BINUTILS_MINOR}

$(call mkcache_append,BINUTILS_VERSION,${binutils_mk_cachefile})
$(call mkcache_append,BINUTILS_MAJOR,${binutils_mk_cachefile})
$(call mkcache_append,BINUTILS_MINOR,${binutils_mk_cachefile})
$(call mkcache_append,binutils-cflags,${binutils_mk_cachefile})

endif # end of cache

$(eval $(call define_version,binutils,version2_code100010,y,${BINUTILS_MAJOR},${BINUTILS_MINOR}))

ifdef DEBUG
  $(info Binutils version ${BINUTILS_MAJOR}.${BINUTILS_MINOR})
  $(info BINUTILS_VERSION = ${BINUTILS_VERSION})
  $(info BINUTILS_MAJOR = ${BINUTILS_MAJOR})
  $(info BINUTILS_MINOR = ${BINUTILS_MINOR})
  $(info binutils-cflags = ${binutils-cflags})
endif

ifneq (${BINUTILS_MAJOR},2)
  $(error Not support binutils major=${BINUTILS_VERSION}, only major==2)
endif

ifdef TEST
  # newest binutils is 2.47
  ifneq ($(call binutils_gt,2,47,0), n)
    $(error call binutils_gt failed, $(call binutils_gt,2,47,0))
  endif
endif # end of TEST

export BINUTILS_VERSION
export BINUTILS_MAJOR
export BINUTILS_MINOR
export binutils-cflags

endif
