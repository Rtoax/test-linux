# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output definitions:
# - HAVE_HPCC=y
# - HAVE_HCDNN=y
# - HPCC_ROOT
# - HTCC
# - HPCC_VERSION_MAJOR
# - HPCC_VERSION_MINOR
# - HPCC_VERSION_PATCH
#
# Modify definitions:
# - target-htcc-y
# - target-htcc-liba-y
# - target-htcc-libso-y

_HPCC_MK = 1

include define.mk

HPCC_ROOT := /opt/hpcc
HPCC_ROOT := $(shell realpath ${HPCC_ROOT} 2>/dev/null || true)
HPCC_CU_BRIDGE := ${HPCC_ROOT}/tools/cu-bridge/include/
HPCC_LLVM := ${HPCC_ROOT}/htgpu_llvm/
HTCC := ${HPCC_LLVM}/bin/htcc

ifeq ($(wildcard $(HTCC)),)
  ifneq ($(target-htcc-y)$(target-htcc-liba-y)$(target-htcc-libso-y),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found htcc with target htcc not empty, but __IGNORE_NOTFOUND_ERROR__)
      target-htcc-y :=
      target-htcc-liba-y :=
      target-htcc-libso-y :=
    else
      $(error Not found htcc with target htcc not empty, install hpcc first)
    endif
  endif
endif

ifneq ($(wildcard ${HPCC_ROOT}),)
  GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
  HPCC_VERSION_RAW := $(shell echo ${HPCC_ROOT} | ${GREP} | head -1)
  HPCC_VERSION_MAJOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$1}')
  HPCC_VERSION_MINOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$2}')
  HPCC_VERSION_PATCH := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$3}')

  HAVE_HPCC := y
  export HAVE_HPCC
else
  $(warning Not found HPCC_ROOT="${HPCC_ROOT}")
  HPCC_VERSION_MAJOR :=
  HPCC_VERSION_MINOR :=
  HPCC_VERSION_PATCH :=
endif

ifneq (${HPCC_ROOT},)
  ifeq (${HTCC},)
    $(error Found ${HPCC_ROOT}, but not found htcc, do you set ENV correctly???)
  endif
endif

$(call check_file_and_def,${HPCC_ROOT}/include/hcdnn/hcdnn.h,HAVE_HCDNN)

export HPCC_ROOT HTCC
export HPCC_VERSION_MAJOR HPCC_VERSION_MINOR HPCC_VERSION_PATCH

ifdef DEBUG
  $(info HAVE_HPCC = ${HAVE_HPCC})
  $(info HPCC_ROOT = ${HPCC_ROOT})
  $(info HTCC = ${HTCC})
  ifneq ($(HTCC),)
    $(info $(shell ${HTCC} --version))
  endif
  $(info HPCC_VERSION_RAW = ${HPCC_VERSION_RAW})
  $(info HPCC_VERSION_MAJOR = ${HPCC_VERSION_MAJOR})
  $(info HPCC_VERSION_MINOR = ${HPCC_VERSION_MINOR})
  $(info HPCC_VERSION_PATCH = ${HPCC_VERSION_PATCH})
endif
