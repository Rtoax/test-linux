# SPDX-License-Identifier: GPL-3.0
# https://www.metax-tech.com/
# Copyright (c) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output macros:
# - HAVE_HPCC
# - HPCC_ROOT
# - MXCC
# - HTCC
# - HPCC_VERSION_MAJOR
# - HPCC_VERSION_MINOR
# - HPCC_VERSION_PATCH

_HPCC = 1

MXCC := $(shell which mxcc 2>/dev/null)
HTCC := $(shell which htcc 2>/dev/null)

HPCC_ROOT := $(shell readlink /opt/hpcc 2>/dev/null || true)
HPCC_CU_BRIDGE := /opt/hpcc/tools/cu-bridge/include/

ifeq ($(MXCC),)
  ifneq ($(targets-mxcc),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found mxcc with targets-mxcc not empty, but __IGNORE_NOTFOUND_ERROR__)
      targets-mxcc :=
    else
      $(error Not found mxcc with targets-mxcc not empty, install MetaX Toolkit first)
    endif
  endif
endif

ifeq ($(HTCC),)
  ifneq ($(targets-htcc),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found htcc with targets-htcc not empty, but __IGNORE_NOTFOUND_ERROR__)
      targets-htcc :=
    else
      $(error Not found htcc with targets-htcc not empty, install MetaX hpcc first)
    endif
  endif
endif

ifneq ($(wildcard ${HPCC_ROOT}),)
  GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
  HPCC_VERSION_RAW := $(shell echo ${HPCC_ROOT} | ${GREP} | head -1)
  HPCC_VERSION_MAJOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$1}')
  HPCC_VERSION_MINOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$2}')
  HPCC_VERSION_PATCH := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$3}')

  HAVE_HPCC := 1
  export HAVE_HPCC
else
  HPCC_VERSION_MAJOR :=
  HPCC_VERSION_MINOR :=
  HPCC_VERSION_PATCH :=
endif

ifneq (${HPCC_ROOT},)
  ifeq (${HTCC},)
    $(error Found ${HPCC_ROOT}, but not found htcc, do you set ENV correctly???)
  endif
endif

export HPCC_ROOT
export MXCC HTCC
export HPCC_VERSION_MAJOR HPCC_VERSION_MINOR HPCC_VERSION_PATCH

ifdef DEBUG
  ifneq ($(targets-mxcc),)
    $(info $(shell ${MXCC} --version))
    $(info MXCC = ${MXCC})
  endif
  ifneq ($(targets-htcc),)
    $(info $(shell ${HTCC} --version))
    $(info HTCC = ${HTCC})
    $(info HPCC_VERSION_RAW = ${HPCC_VERSION_RAW})
    $(info HPCC_VERSION_MAJOR = ${HPCC_VERSION_MAJOR})
    $(info HPCC_VERSION_MINOR = ${HPCC_VERSION_MINOR})
    $(info HPCC_VERSION_PATCH = ${HPCC_VERSION_PATCH})
  endif
endif
