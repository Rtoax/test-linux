# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output definitions:
# - HAVE_LUCA
# - LUCA_ROOT
# - LSCC
# - LUCA_VERSION_MAJOR
# - LUCA_VERSION_MINOR
# - LUCA_VERSION_PATCH

_LUCA = 1

LUCA_ROOT := /opt/luca
LUCA_ROOT := $(shell realpath ${LUCA_ROOT} 2>/dev/null || true)
LUCA_CU_BRIDGE := ${LUCA_ROOT}/tools/cu-bridge/include/
LUCA_LLVM := ${LUCA_ROOT}/htgpu_llvm/
# FIXME: Need rename htcc to lscc
LSCC := ${LUCA_LLVM}/bin/htcc

ifeq ($(LSCC),)
  ifneq ($(target-lscc-y),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found lscc with target-lscc-y not empty, but __IGNORE_NOTFOUND_ERROR__)
      target-lscc-y :=
    else
      $(error Not found lscc with target-lscc-y not empty, install MetaX hpcc first)
    endif
  endif
endif

ifneq ($(wildcard ${LUCA_ROOT}),)
  GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
  LUCA_VERSION_RAW := $(shell echo ${LUCA_ROOT} | ${GREP} | head -1)
  LUCA_VERSION_MAJOR := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$1}')
  LUCA_VERSION_MINOR := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$2}')
  LUCA_VERSION_PATCH := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$3}')

  HAVE_LUCA := 1
  export HAVE_LUCA
else
  $(warning Not found LUCA_ROOT="${LUCA_ROOT}")
  LUCA_VERSION_MAJOR :=
  LUCA_VERSION_MINOR :=
  LUCA_VERSION_PATCH :=
endif

ifneq (${LUCA_ROOT},)
  ifeq (${LSCC},)
    $(error Found ${LUCA_ROOT}, but not found lscc, do you set ENV correctly???)
  endif
endif

export LUCA_ROOT
export LSCC
export LUCA_VERSION_MAJOR LUCA_VERSION_MINOR LUCA_VERSION_PATCH

ifdef DEBUG
  $(info LUCA_ROOT = ${LUCA_ROOT})
  $(info LSCC = ${LSCC})
  $(info $(shell ${LSCC} --version))
  $(info LUCA_VERSION_RAW = ${LUCA_VERSION_RAW})
  $(info LUCA_VERSION_MAJOR = ${LUCA_VERSION_MAJOR})
  $(info LUCA_VERSION_MINOR = ${LUCA_VERSION_MINOR})
  $(info LUCA_VERSION_PATCH = ${LUCA_VERSION_PATCH})
endif
