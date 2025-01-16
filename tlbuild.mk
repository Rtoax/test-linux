# SPDX-License-Identifier: GPL-3.0
SHELL = bash

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
else
  Q = @
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

USER_FAILED_LOG := $(TL_TOPDIR)/failed-user.log
KERNEL_FAILED_LOG := $(TL_TOPDIR)/failed-kernel.log
export USER_FAILED_LOG KERNEL_FAILED_LOG

