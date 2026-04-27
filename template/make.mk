# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Export:
# - MAKE=[make_tl.sh]
#
# Functions:
# - make_{gt,ge,eq,lt,le}()=[y|n]
#
ifndef _MAKE_MK
_MAKE_MK = 1

include dir.mk
include version.mk

MAKE := ${TOPDIR}/scripts/make_tl.sh

makeversh = ${TOPDIR}/scripts/version/make.sh

MAKE_VERSION := $(shell ${makeversh})
MAKE_MAJOR := $(shell ${makeversh} --major)
MAKE_MINOR := $(shell ${makeversh} --minor)

$(eval $(call define_version,make,version2_code100010,${MAKE_MAJOR},${MAKE_MINOR}))

ifneq ($(call make_ge,4,5), n)
  $(error make_ge failed, $(call make_ge,4,4))
endif

ifdef DEBUG
  $(info MAKE = ${MAKE})
  $(info MAKE_VERSION = ${MAKE_VERSION})
  $(info MAKE_MAJOR = ${MAKE_MAJOR})
  $(info MAKE_MINOR = ${MAKE_MINOR})
endif

endif
