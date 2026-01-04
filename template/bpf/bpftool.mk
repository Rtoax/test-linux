# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - BPFTOOL=
# - BPFTOOL_VERSION_MAJOR=
# - BPFTOOL_VERSION_MINOR=
#
_BPF_BPFTOOL_MK = 1

BPFTOOL := $(shell which bpftool 2>/dev/null)
ifeq ($(BPFTOOL),)
  ifneq ($(wildcard /usr/sbin/bpftool),)
    BPFTOOL := /usr/sbin/bpftool
  else
    $(error "Not found bpftool, install first")
  endif
endif

BPFTOOL_VERSION := $(shell ${BPFTOOL} --version | grep -w bpftool | grep -o [0-9].[0-9]\. | sed -n '1p')
BPFTOOL_VERSION_MAJOR := $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$1}')
BPFTOOL_VERSION_MINOR := $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$2}')

export BPFTOOL BPFTOOL_VERSION_MAJOR BPFTOOL_VERSION_MINOR

ifdef DEBUG
  $(info ${BPFTOOL} version ${BPFTOOL_VERSION_MAJOR}.${BPFTOOL_VERSION_MINOR})
endif
