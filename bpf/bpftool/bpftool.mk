# SPDX-License-Identifier: GPL-3.0
SHELL := bash

BPFTOOL := $(shell which bpftool 2>/dev/null)
ifeq ($(BPFTOOL),)
  $(error "Not found bpftool, install first")
endif

BPFTOOL_VERSION = $(shell ${BPFTOOL} --version | grep -w bpftool | grep -o [0-9].[0-9]\. | sed -n '1p')
BPFTOOL_VERSION_MAJOR = $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$1}')
BPFTOOL_VERSION_MINOR = $(shell echo ${BPFTOOL_VERSION} | awk -F '.' '{print $$2}')

$(info ${BPFTOOL} version ${BPFTOOL_VERSION_MAJOR}.${BPFTOOL_VERSION_MINOR})
export BPFTOOL BPFTOOL_VERSION_MAJOR BPFTOOL_VERSION_MINOR
