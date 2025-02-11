# SPDX-License-Identifier: GPL-3.0
SHELL := bash

RUSTC := $(shell which rustc 2>/dev/null)
ifeq ($(RUSTC),)
  $(error "Not found rustc compiler")
endif

