# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Makefile builtin:
# - CURDIR=[]
# - HOME=[/home/rongtao/]
#
# Output definitions:
# - TOPDIR=
#
# Functions:
# - strip_topdir_prefix()
#
ifndef _DIR_MK
_DIR_MK = 1

TOPDIR := $(dir $(shell realpath $(abspath $(lastword $(MAKEFILE_LIST))/../)))

ifeq (${TOPDIR},)
  $(error Could not found top directory in anywhere)
endif

# remove test-linux root directory from $1
define strip_topdir_prefix
$(patsubst ${TOPDIR}%,%,$(1))
endef

ifdef DEBUG
  $(info TOPDIR = ${TOPDIR})
endif

export TOPDIR

endif
