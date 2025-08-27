# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
_DIR = 1

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

TOPDIR := ${GIT_TOPDIR}
ifeq (${TOPDIR},)
  TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))/../))
endif

ifeq (${TOPDIR},)
  $(error Could not found topdir in anywhere)
endif

export TOPDIR GIT_TOPDIR
