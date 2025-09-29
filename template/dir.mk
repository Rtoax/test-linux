# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
_DIR = 1

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

TOPDIR := ${GIT_TOPDIR}
ifeq (${TOPDIR},)
  TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))/../))
endif

CURDIR := $(shell realpath .)

ifeq (${TOPDIR},)
  $(error Could not found top directory in anywhere)
endif

ifeq (${CURDIR},)
  $(error Could not found current directory in anywhere)
endif

define git_relative_dir
$(patsubst ${GIT_TOPDIR}/%,%,$(1))
endef

ifdef DEBUG
  $(info TOPDIR = ${TOPDIR})
  $(info CURDIR = ${CURDIR})
endif

export TOPDIR CURDIR GIT_TOPDIR
