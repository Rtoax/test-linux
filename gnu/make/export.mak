# SPDX-License-Identifier: GPL-3.0

include verbose.mk

ifndef _VERBOSE_MK
  $(error "Need verbose.mk")
endif

.PHONY: build
build:
