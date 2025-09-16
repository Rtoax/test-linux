# SPDX-License-Identifier: GPL-3.0
# https://www.metax-tech.com/
_HPCC = 1

MXCC := $(shell which mxcc 2>/dev/null)
HTCC := $(shell which htcc 2>/dev/null)

HPCC_REALPATH := $(shell readlink /opt/hpcc 2>/dev/null || true)
HPCC_CU_BRIDGE := /opt/hpcc/tools/cu-bridge/include/

ifeq ($(MXCC),)
  ifneq ($(targets-mxcc),)
    $(error Not found mxcc, install MetaX Toolkit first)
  endif
endif
ifeq ($(HTCC),)
  ifneq ($(targets-htcc),)
    $(error Not found htcc, install MetaX hpcc first)
  endif
endif

ifneq ($(wildcard ${HPCC_REALPATH}),)
  GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
  HPCC_VERSION_RAW := $(shell echo ${HPCC_REALPATH} | ${GREP} | head -1)
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
