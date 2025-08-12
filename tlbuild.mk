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

TL_LOG := $(TOPDIR)/test-linux.log
TL_FAILED_LOG := $(TOPDIR)/failed.log
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
