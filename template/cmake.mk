# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _CMAKE_MK
_CMAKE_MK = 1

include dir.mk
include version.mk

CMAKE_VERSION := $(shell ${TOPDIR}/tools/cmake/version.sh)
CMAKE_MAJOR := $(shell ${TOPDIR}/tools/cmake/version.sh --major)
CMAKE_MINOR := $(shell ${TOPDIR}/tools/cmake/version.sh --minor)
CMAKE_PATCHLEVEL := $(shell ${TOPDIR}/tools/cmake/version.sh --patchlevel)

ifdef DEBUG
  $(info CMAKE_VERSION = ${CMAKE_VERSION})
  $(info CMAKE_MAJOR = ${CMAKE_MAJOR})
  $(info CMAKE_MINOR = ${CMAKE_MINOR})
  $(info CMAKE_PATCHLEVEL = ${CMAKE_PATCHLEVEL})
endif

endif
