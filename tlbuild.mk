# SPDX-License-Identifier: GPL-3.0
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

CPU_VENDOR_ID=$(shell lscpu | grep ^Vendor | awk '{print $$3}')

# GIT_TOPDIR is empty if not in git-repo.
GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)
TL_TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LIBS_TOPDIR := $(TL_TOPDIR)/libs/
NUMA_TOPDIR := $(TL_TOPDIR)/numa/

export GIT_TOPDIR TL_TOPDIR LIBS_TOPDIR NUMA_TOPDIR

TL_LOG := $(TL_TOPDIR)/log.log
USER_FAILED_LOG := $(TL_TOPDIR)/failed-user.log
KERNEL_FAILED_LOG := $(TL_TOPDIR)/failed-kernel.log
export TL_LOG USER_FAILED_LOG KERNEL_FAILED_LOG

define tl_log
	${Q}echo $(shell date '+%Y-%m-%d_%H:%M:%S') $(shell hostname) $1 >> ${TL_LOG}
endef

define cleanuserlog
	${Q}rm -f $(USER_FAILED_LOG)
endef

define cleankernellog
	${Q}rm -f $(KERNEL_FAILED_LOG)
endef

define printuserlog
	@if [[ -e $(USER_FAILED_LOG) ]]; then \
		${Q}cat $(USER_FAILED_LOG) ; \
	fi
endef

define printkernellog
	@if [[ -e $(KERNEL_FAILED_LOG) ]]; then \
		${Q}cat $(KERNEL_FAILED_LOG) ; \
	fi
endef

