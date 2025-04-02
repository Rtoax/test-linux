# SPDX-License-Identifier: GPL-3.0
# WARNING: Could not include this mk in kernel module Makefile, only for user
# space.
#
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

ifdef M32
  MAKEFLAGS += M32=1
endif
export MAKEFLAGS

CPU_VENDOR_ID=$(shell lscpu | grep ^Vendor | awk '{print $$3}')

# GIT_TOPDIR is empty if not in git-repo.
GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)
TL_TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LIBS_TOPDIR := $(TL_TOPDIR)/libs/
NUMA_TOPDIR := $(TL_TOPDIR)/numa/

export GIT_TOPDIR TL_TOPDIR LIBS_TOPDIR NUMA_TOPDIR

TL_LOG := $(TL_TOPDIR)/test-linux.log
FAILED_LOG := $(TL_TOPDIR)/failed.log
export TL_LOG FAILED_LOG

define tl_log
	${Q}echo $(shell date '+%Y-%m-%d_%H:%M:%S') $(shell hostname) $1 >> ${TL_LOG}
endef

define cleanfailedlog
	${Q}rm -f $(FAILED_LOG)
endef

define printfailedlog
	${Q}if [[ -e $(FAILED_LOG) ]]; then \
		cat $(FAILED_LOG) ; \
	fi
endef

