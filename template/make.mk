# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _MAKE_MK
_MAKE_MK = 1

include dir.mk
include version.mk

MAKE_VERSION := $(shell ${TOPDIR}/gnu/make/version.sh)
MAKE_MAJOR := $(shell ${TOPDIR}/gnu/make/version.sh --major)
MAKE_MINOR := $(shell ${TOPDIR}/gnu/make/version.sh --minor)

ifdef DEBUG
  $(info MAKE_VERSION = ${MAKE_VERSION})
  $(info MAKE_MAJOR = ${MAKE_MAJOR})
  $(info MAKE_MINOR = ${MAKE_MINOR})
endif

endif
