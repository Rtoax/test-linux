# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_BPFTRACE=y
# - BPFTRACE=
# - BPFTRACE_VERSION_MAJOR=
# - BPFTRACE_VERSION_MINOR=
#
ifndef _BPFTRACE_MK
_BPFTRACE_MK = 1

BPFTRACE := $(shell which bpftrace 2>/dev/null)
ifeq ($(BPFTRACE),)
  $(error "Not found bpftrace, install first")
endif

HAVE_BPFTRACE := y

BPFTRACE_VERSION := $(shell ${BPFTRACE} --version | grep -o v[0-9].[0-9]\. | sed -n '1p')
BPFTRACE_VERSION_MAJOR := $(shell echo ${BPFTRACE_VERSION} | awk -F '.' '{print $$1}')
BPFTRACE_VERSION_MINOR := $(shell echo ${BPFTRACE_VERSION} | awk -F '.' '{print $$2}')

export HAVE_BPFTRACE
export BPFTRACE BPFTRACE_VERSION_MAJOR BPFTRACE_VERSION_MINOR

ifdef DEBUG
  $(info ${BPFTRACE} version ${BPFTRACE_VERSION_MAJOR}.${BPFTRACE_VERSION_MINOR})
endif

endif
