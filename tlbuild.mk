# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
# WARNING: Could not include this mk in kernel module Makefile, only for user
# space.
SHELL := bash

comma	:= ,
quota	:= "
squote	:= '
empty   :=
space   := $(empty) $(empty)
space_escape := _-_SPACE_-_
pound	:= \#
define newline

endef

ifeq ($(V),1)
  Q =
  MAKEFLAGS += V=1
else
  Q = @
  MAKEFLAGS += --silent
  MAKEFLAGS += --no-print-directory
endif
export Q

# GIT_TOPDIR is empty if not in git-repo.
GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)
TL_TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LIBS_TOPDIR := $(TL_TOPDIR)/libs/
NUMA_TOPDIR := $(TL_TOPDIR)/numa/

export GIT_TOPDIR TL_TOPDIR LIBS_TOPDIR NUMA_TOPDIR

TL_LOG := $(TL_TOPDIR)/test-linux.log
TL_FAILED_LOG := $(TL_TOPDIR)/failed.log
export TL_LOG TL_FAILED_LOG

define tl_log
	${Q}echo $(shell date '+%Y-%m-%d %H:%M:%S') $(shell hostname) $1 >> ${TL_LOG}
endef

define cleanfailedlog
	${Q}rm -f $(TL_FAILED_LOG)
endef

define printfailedlog
	${Q}if [[ -e $(TL_FAILED_LOG) ]]; then \
		cat $(TL_FAILED_LOG) ; \
	fi
endef
