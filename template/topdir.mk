# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)
TL_TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/../

TOPDIR := ${GIT_TOPDIR}
ifeq (${TOPDIR},)
  TOPDIR := ${TL_TOPDIR}
endif

ifeq (${TOPDIR},)
  $(error Could not found topdir in anywhere)
endif
