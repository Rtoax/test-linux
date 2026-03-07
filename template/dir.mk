# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - TOPDIR=
# - CURDIR=
#
# Functions:
# - strip_topdir_prefix()
#
ifndef _DIR_MK
export _DIR_MK = 1

TOPDIR := $(dir $(shell realpath $(abspath $(lastword $(MAKEFILE_LIST))/../)))
CURDIR := $(shell realpath .)

ifeq (${TOPDIR},)
  $(error Could not found top directory in anywhere)
endif

ifeq (${CURDIR},)
  $(error Could not found current directory in anywhere)
endif

# remove test-linux root directory from $1
define strip_topdir_prefix
$(patsubst ${TOPDIR}%,%,$(1))
endef

ifdef DEBUG
  $(info TOPDIR = ${TOPDIR})
  $(info CURDIR = ${CURDIR})
endif

export TOPDIR CURDIR

endif
