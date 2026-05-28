# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
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
include version.mk

$(call find_cmd_and_def,cmake)

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

$(eval $(call define_version,cmake,version3_code1688,${CMAKE_MAJOR},${CMAKE_MINOR},${CMAKE_PATCHLEVEL}))

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
