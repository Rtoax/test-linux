# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - cmake_{gt,ge,eq,lt,le}()=[y|n]
#
ifndef _CMAKE_MK
_CMAKE_MK = 1

include dir.mk
include version.mk

cmakeversh = ${TOPDIR}/scripts/version/cmake.sh

CMAKE_VERSION := $(shell ${cmakeversh})
CMAKE_MAJOR := $(shell ${cmakeversh} --major)
CMAKE_MINOR := $(shell ${cmakeversh} --minor)
CMAKE_PATCHLEVEL := $(shell ${cmakeversh} --patchlevel)

CMAKE_VERSION_CODE := $(call version3_code1688,${CMAKE_MAJOR},${CMAKE_MINOR},${CMAKE_PATCHLEVEL})

define cmake_gt
$(call version3_code1688_cmp,${CMAKE_VERSION_CODE},-gt,${1},${2},${3})
endef
define cmake_ge
$(call version3_code1688_cmp,${CMAKE_VERSION_CODE},-ge,${1},${2},${3})
endef
define cmake_eq
$(call version3_code1688_cmp,${CMAKE_VERSION_CODE},-eq,${1},${2},${3})
endef
define cmake_lt
$(call version3_code1688_cmp,${CMAKE_VERSION_CODE},-lt,${1},${2},${3})
endef
define cmake_le
$(call version3_code1688_cmp,${CMAKE_VERSION_CODE},-le,${1},${2},${3})
endef

ifdef DEBUG
  $(info CMAKE_VERSION = ${CMAKE_VERSION})
  $(info CMAKE_MAJOR = ${CMAKE_MAJOR})
  $(info CMAKE_MINOR = ${CMAKE_MINOR})
  $(info CMAKE_PATCHLEVEL = ${CMAKE_PATCHLEVEL})
endif

endif
