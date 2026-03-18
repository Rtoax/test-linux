# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
#
# Output definitions:
# - GCC=[gcc]
# - GXX=[g++]
# - GCC_VERSION=
# - GCC_MAJOR=
# - GCC_MINOR=
# - GCC_PATCHLEVEL=
# - GCC_VERSION_CODE=
#
# Functions:
# - gcc_gt()=[y|n]
# - gcc_ge()=[y|n]
# - gcc_eq()=[y|n]
# - gcc_le()=[y|n]
# - gcc_lt()=[y|n]
#
ifndef _GCC_MK
_GCC_MK = 1

include dir.mk

GCC := gcc
GXX := g++

CC ?= ${GCC}
CXX ?= ${GXX}

gccversh = ${TOPDIR}/scripts/version/gcc.sh

GCC_VERSION := $(shell ${gccversh})
GCC_MAJOR := $(shell ${gccversh} --major)
GCC_MINOR := $(shell ${gccversh} --minor)
GCC_PATCHLEVEL := $(shell ${gccversh} --patchlevel)

include compiler.mk
include version.mk

GCC_VERSION_CODE := $(call version3_code1688,${GCC_MAJOR},${GCC_MINOR},${GCC_PATCHLEVEL})

define gcc_gt
$(call version3_code1688_cmp,${GCC_VERSION_CODE},-gt,${1},${2},${3})
endef
define gcc_ge
$(call version3_code1688_cmp,${GCC_VERSION_CODE},-ge,${1},${2},${3})
endef
define gcc_eq
$(call version3_code1688_cmp,${GCC_VERSION_CODE},-eq,${1},${2},${3})
endef
define gcc_lt
$(call version3_code1688_cmp,${GCC_VERSION_CODE},-lt,${1},${2},${3})
endef
define gcc_le
$(call version3_code1688_cmp,${GCC_VERSION_CODE},-le,${1},${2},${3})
endef

ifdef DEBUG
  $(info GCC = ${GCC})
  $(info GXX = ${GXX})
  $(info GCC_VERSION = ${GCC_VERSION} (${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL}))
  $(info GCC_VERSION_CODE = ${GCC_VERSION_CODE})
endif

# Do some checks
ifneq (${GCC_VERSION},${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
  $(error Failed to parse GCC version, ${GCC_VERSION} != ${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
endif

ifneq ($(call version3_code1688,${GCC_MAJOR},${GCC_MINOR},${GCC_PATCHLEVEL}),${GCC_VERSION_CODE})
  $(error call version3_code1688() failed)
endif

# newest gcc major is 16
ifeq ($(call gcc_gt,17,0,0), y)
  $(error call gcc_gt failed.)
endif

export GCC GXX
export GCC_VERSION GCC_MAJOR GCC_MINOR GCC_PATCHLEVEL
export GCC_VERSION_CODE

endif
