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

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

LIBS_TOPDIR := $(GIT_TOPDIR)/libs/
NUMA_TOPDIR := $(GIT_TOPDIR)/numa/

export GIT_TOPDIR LIBS_TOPDIR NUMA_TOPDIR

