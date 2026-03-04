# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - make_{gt,ge,eq,lt,le}=[y|n]
#
ifndef _MAKE_MK
_MAKE_MK = 1

include dir.mk
include version.mk

MAKE_VERSION := $(shell ${TOPDIR}/gnu/make/version.sh)
MAKE_MAJOR := $(shell ${TOPDIR}/gnu/make/version.sh --major)
MAKE_MINOR := $(shell ${TOPDIR}/gnu/make/version.sh --minor)

MAKE_VERSION_CODE := $(call version2_code100010,${MAKE_MAJOR},${MAKE_MINOR})

define make_gt
$(call version2_code100010_cmp,${MAKE_VERSION_CODE},-gt,${1},${2})
endef
define make_ge
$(call version2_code100010_cmp,${MAKE_VERSION_CODE},-ge,${1},${2})
endef
define make_eq
$(call version2_code100010_cmp,${MAKE_VERSION_CODE},-eq,${1},${2})
endef
define make_lt
$(call version2_code100010_cmp,${MAKE_VERSION_CODE},-lt,${1},${2})
endef
define make_le
$(call version2_code100010_cmp,${MAKE_VERSION_CODE},-le,${1},${2})
endef

ifdef DEBUG
  $(info MAKE_VERSION = ${MAKE_VERSION})
  $(info MAKE_MAJOR = ${MAKE_MAJOR})
  $(info MAKE_MINOR = ${MAKE_MINOR})
  $(info MAKE_VERSION_CODE = ${MAKE_VERSION_CODE})
endif

endif
