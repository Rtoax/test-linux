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
ifndef _GCC_MK
_GCC_MK = 1

GCC := gcc
GXX := g++

CC = ${GCC}
CXX = ${GXX}

GCC_FULLVERSION := $(shell $(GCC) -dumpfullversion -dumpversion)
GCC_VERSION := $(shell $(GCC) -dumpversion)
GCC_MAJOR := $(shell echo ${GCC_FULLVERSION} | awk -F '.' '{print $$1}')
GCC_MINOR := $(shell echo ${GCC_FULLVERSION} | awk -F '.' '{print $$2}')
GCC_PATCHLEVEL := $(shell echo ${GCC_FULLVERSION} | awk -F '.' '{print $$3}')

include compiler.mk

GCC_VERSION_CODE := $(shell echo "$$(( (${GCC_MAJOR}<<16) + (${GCC_MINOR}<<8) + (${GCC_PATCHLEVEL}>255?255:${GCC_PATCHLEVEL}) ))" )

ifdef DEBUG
  $(info GCC = ${GCC})
  $(info GXX = ${GXX})
  $(info GCC_FULLVERSION = ${GCC_FULLVERSION})
  $(info GCC_VERSION = ${GCC_VERSION} (${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL}))
  $(info GCC_VERSION_CODE = ${GCC_VERSION_CODE})
endif

ifneq (${GCC_VERSION},${GCC_MAJOR}.${GCC_MINOR}.${GCC_PATCHLEVEL})
  $(error Failed to parse GCC version)
endif

export GCC GXX
export GCC_FULLVERSION GCC_VERSION GCC_MAJOR GCC_MINOR GCC_PATCHLEVEL
export GCC_VERSION_CODE

endif
