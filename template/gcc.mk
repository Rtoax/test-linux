# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
#
# Output definitions:
# - GCC=[gcc]
# - GXX=[g++]
# - GCC_FULLVERSION=
# - GCC_VERSION=
# - GCC_MAJOR=
# - GCC_MINOR=
# - GCC_PATCHLEVEL=
# - GCC_VERSION_CODE=
#
# Functions:
# - gcc_version_code()
# - gcc_version_compare()=[y|n]
# - gcc_gt()=[y|n]
# - gcc_ge()=[y|n]
# - gcc_eq()=[y|n]
# - gcc_le()=[y|n]
# - gcc_lt()=[y|n]
#
ifndef _GCC_MK
_GCC_MK = 1

GCC := gcc
GXX := g++

CC ?= ${GCC}
CXX ?= ${GXX}

GCC_FULLVERSION := $(shell $(GCC) -dumpfullversion)
GCC_VERSION := $(shell $(GCC) -dumpversion)
GCC_MAJOR := $(shell echo ${GCC_FULLVERSION} | awk -F '.' '{print $$1}')
GCC_MINOR := $(shell echo ${GCC_FULLVERSION} | awk -F '.' '{print $$2}')
GCC_PATCHLEVEL := $(shell echo ${GCC_FULLVERSION} | awk -F '.' '{print $$3}')

include compiler.mk

GCC_VERSION_CODE := $(shell echo "$$(( (${GCC_MAJOR}<<16) + (${GCC_MINOR}<<8) + (${GCC_PATCHLEVEL}>255?255:${GCC_PATCHLEVEL}) ))" )

define gcc_version_code
$(shell echo "$$(( (${1}<<16) + (${2}<<8) + (${3}>255?255:${3}) ))" )
endef

# Arguments:
# $1: [-gt|-ge|-eq|-lt|-le]
# $2: major
# $3: minor
# $4: patchlevel
define gcc_version_compare
$(shell if [[ ${GCC_VERSION_CODE} ${1} $(call gcc_version_code,${2},${3},${4}) ]]; then \
		echo y; \
	else echo n; \
	fi)
endef

define gcc_gt
$(call gcc_version_compare,-gt,${1},${2},${3})
endef
define gcc_ge
$(call gcc_version_compare,-ge,${1},${2},${3})
endef
define gcc_eq
$(call gcc_version_compare,-eq,${1},${2},${3})
endef
define gcc_lt
$(call gcc_version_compare,-lt,${1},${2},${3})
endef
define gcc_le
$(call gcc_version_compare,-le,${1},${2},${3})
endef

ifdef DEBUG
  $(info GCC = ${GCC})
  $(info GXX = ${GXX})
  $(info GCC_FULLVERSION = ${GCC_FULLVERSION})
  $(info GCC_VERSION = ${GCC_VERSION} (${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL}))
  $(info GCC_VERSION_CODE = ${GCC_VERSION_CODE})
endif

# Do some checks
ifneq (${GCC_FULLVERSION},${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
  $(error Failed to parse GCC version, ${GCC_FULLVERSION} != ${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
endif

ifneq ($(call gcc_version_code,${GCC_MAJOR},${GCC_MINOR},${GCC_PATCHLEVEL}),${GCC_VERSION_CODE})
  $(error call gcc_version_code() failed)
endif

# newest gcc major is 16
ifeq ($(call gcc_gt,17,0,0), y)
  $(error call gcc_gt failed.)
endif

export GCC GXX
export GCC_FULLVERSION GCC_VERSION GCC_MAJOR GCC_MINOR GCC_PATCHLEVEL
export GCC_VERSION_CODE

endif
