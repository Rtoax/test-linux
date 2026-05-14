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
# - list_dir()
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

# List all directory in current directory
# $1: directory to listing, optional, current directory if not pass.
define list_dir
$(shell find ${1} -maxdepth 1 -mindepth 1 -type d -printf '%f\n')
endef

ifdef DEBUG
  $(info TOPDIR = ${TOPDIR})
  $(info HOME = ${HOME})
  $(info list_dir = $(call list_dir, ..))
endif

ifneq ($(call strip_topdir_prefix,${TOPDIR}/rong/tao),/rong/tao)
  $(error strip_topdir_prefix test failed)
endif

export TOPDIR

endif
