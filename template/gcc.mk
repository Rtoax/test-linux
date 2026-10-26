# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Input definitions:
#
# Output definitions:
# - HAVE_GCC=[y|n]
# - HAVE_GXX=[y|n]
# - GCC=[/usr/bin/gcc]
# - GXX=[/usr/bin/g++]
# - GCC_VERSION=
# - GCC_MAJOR=
# - GCC_MINOR=
# - GCC_PATCHLEVEL=
# - GCC_MACHINE=[x86_64-linux-gnu]
#
# Functions:
# - gcc_{gt,ge,eq,lt,le}(major, minor, patchlevel)=[y|n]
#
ifndef _GCC_MK
_GCC_MK = 1

include dir.mk
include define.mk
include shell.mk
include version.mk

$(call find_cmd_and_def,gcc)
$(call find_cmd_and_def,g++,gxx)

CC ?= ${GCC}
CXX ?= ${GXX}

gcc_mk_cachefile := ${TOPDIR}/template/.gcc.mk.cache
gcc_mk_origfile := ${TOPDIR}/template/gcc.mk
ifeq ($(call is_newer,${gcc_mk_cachefile},${gcc_mk_origfile}),y)
  include ${gcc_mk_cachefile}
else

include bits/mk-cache.mk

$(call make_gen_cachefile,${gcc_mk_cachefile})

gccversh = ${TOPDIR}/scripts/version/gcc.sh

GCC_VERSION := $(shell ${gccversh})
GCC_MAJOR := $(shell ${gccversh} --major)
GCC_MINOR := $(shell ${gccversh} --minor)
GCC_PATCHLEVEL := $(shell ${gccversh} --patchlevel)
GCC_MACHINE := $(shell ${GCC} -dumpmachine)

$(call make_append_var_to_file,GCC_VERSION,${gcc_mk_cachefile})
$(call make_append_var_to_file,GCC_MAJOR,${gcc_mk_cachefile})
$(call make_append_var_to_file,GCC_MINOR,${gcc_mk_cachefile})
$(call make_append_var_to_file,GCC_PATCHLEVEL,${gcc_mk_cachefile})
$(call make_append_var_to_file,GCC_MACHINE,${gcc_mk_cachefile})

endif # end of cache

include compiler.mk

$(eval $(call define_version,gcc,version3_code1688,y,${GCC_MAJOR},${GCC_MINOR},${GCC_PATCHLEVEL}))

ifdef DEBUG
  $(info GCC = ${GCC})
  $(info GXX = ${GXX})
  $(info GCC_VERSION = ${GCC_VERSION} (${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL}))
  $(info GCC_MACHINE = ${GCC_MACHINE})
endif

ifdef TEST
  # Do some checks
  ifneq (${GCC_VERSION},${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
    $(error Failed to parse GCC version, ${GCC_VERSION} != ${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
  endif

  # newest gcc major is 16
  ifneq ($(call gcc_gt,17,0,0), n)
    $(error call gcc_gt failed, $(call gcc_gt,17,0,0))
  endif
endif # end of TEST

export GCC GXX
export GCC_VERSION GCC_MAJOR GCC_MINOR GCC_PATCHLEVEL

endif # end of _GCC_MK
