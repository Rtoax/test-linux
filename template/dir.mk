# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output definitions:
# - TOPDIR
# - CURDIR
#
_DIR = 1

TOPDIR := $(dir $(shell realpath $(abspath $(lastword $(MAKEFILE_LIST))/../)))
CURDIR := $(shell realpath .)

ifeq (${TOPDIR},)
  $(error Could not found top directory in anywhere)
endif

ifeq (${CURDIR},)
  $(error Could not found current directory in anywhere)
endif

define relative_path
$(patsubst ${TOPDIR}%,%,$(1))
endef

ifdef DEBUG
  $(info TOPDIR = ${TOPDIR})
  $(info CURDIR = ${CURDIR})
endif

export TOPDIR CURDIR
