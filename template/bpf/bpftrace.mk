# SPDX-License-Identifier: GPL-3.0
_BPFTRACE = 1

BPFTRACE := $(shell which bpftrace 2>/dev/null)
ifeq ($(BPFTRACE),)
  ifneq ($(wildcard /usr/bin/bpftrace),)
    BPFTRACE := /usr/bin/bpftrace
  else
    $(error "Not found bpftrace, install first")
  endif
endif

BPFTRACE_VERSION := $(shell ${BPFTRACE} --version | grep -o v[0-9].[0-9]\. | sed -n '1p')
BPFTRACE_VERSION_MAJOR := $(shell echo ${BPFTRACE_VERSION} | awk -F '.' '{print $$1}')
BPFTRACE_VERSION_MINOR := $(shell echo ${BPFTRACE_VERSION} | awk -F '.' '{print $$2}')

ifdef DEBUG
  $(info ${BPFTRACE} version ${BPFTRACE_VERSION_MAJOR}.${BPFTRACE_VERSION_MINOR})
endif
export BPFTRACE BPFTRACE_VERSION_MAJOR BPFTRACE_VERSION_MINOR
