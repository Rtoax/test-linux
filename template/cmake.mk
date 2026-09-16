# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Export:
# - HAVE_CMAKE=[y|n]
# - CMAKE=[/usr/bin/cmake]
#
# Functions:
# - cmake_{gt,ge,eq,lt,le}()=[y|n]
#
ifndef _CMAKE_MK
_CMAKE_MK = 1

include define.mk
include dir.mk
include file.mk
include version.mk

$(call find_cmd_and_def,cmake)

cmake_mk_cachefile := ${TOPDIR}/template/.cmake.mk.cache
cmake_mk_origfile := ${TOPDIR}/template/cmake.mk

ifeq ($(call is_newer,${cmake_mk_cachefile},${cmake_mk_origfile}),y)
  include ${cmake_mk_cachefile}
else

include bits/mk-cache.mk

$(call make_gen_cachefile,${cmake_mk_cachefile})

# Get cmake version first
ifneq (${CMAKE},)
  cmakeversh = ${TOPDIR}/scripts/version/cmake.sh

  CMAKE_VERSION := $(shell ${cmakeversh})
  CMAKE_MAJOR := $(shell ${cmakeversh} --major)
  CMAKE_MINOR := $(shell ${cmakeversh} --minor)
  CMAKE_PATCHLEVEL := $(shell ${cmakeversh} --patchlevel)
else
  CMAKE_VERSION := 0.0.0
  CMAKE_MAJOR := 0
  CMAKE_MINOR := 0
  CMAKE_PATCHLEVEL := 0
endif

$(call make_append_var_to_file,CMAKE_VERSION,${cmake_mk_cachefile})
$(call make_append_var_to_file,CMAKE_MAJOR,${cmake_mk_cachefile})
$(call make_append_var_to_file,CMAKE_MINOR,${cmake_mk_cachefile})
$(call make_append_var_to_file,CMAKE_PATCHLEVEL,${cmake_mk_cachefile})

endif # end of cache

$(eval $(call define_version,cmake,version3_code1688,y,${CMAKE_MAJOR},${CMAKE_MINOR},${CMAKE_PATCHLEVEL}))

ifdef DEBUG
  $(info CMAKE_VERSION = ${CMAKE_VERSION})
  $(info CMAKE_MAJOR = ${CMAKE_MAJOR})
  $(info CMAKE_MINOR = ${CMAKE_MINOR})
  $(info CMAKE_PATCHLEVEL = ${CMAKE_PATCHLEVEL})
endif

# newest cmake major is 4
ifneq ($(call cmake_gt,5,0,0), n)
  $(error call cmake_gt failed, cmake major is bigger than 5)
endif

endif
