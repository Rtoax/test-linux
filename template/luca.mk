# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output definitions:
# - HAVE_LUCA=y
# - HAVE_LCDNN=y
# - HAVE_LCFILE=y
# - LUCA_ROOT=
# - LUCA_PHASE_II_PROJECT=  In the second phase of LUCA development, the
#                           filename changed, and the definition was deleted
#                           once development was completed.
# - LSCC=
# - LUCA_VERSION_MAJOR=
# - LUCA_VERSION_MINOR=
# - LUCA_VERSION_PATCH=

_LUCA = 1

include define.mk

LUCA_ROOT := /opt/luca
LUCA_ROOT := $(shell realpath ${LUCA_ROOT} 2>/dev/null || true)
LUCA_CU_BRIDGE := ${LUCA_ROOT}/tools/cu-bridge/include/
LUCA_LLVM := ${LUCA_ROOT}/htgpu_llvm/
# Note: During the LUCA development process, the path and file name changed.
ifeq ($(wildcard ${LUCA_LLVM}),)
  LUCA_LLVM := ${LUCA_ROOT}/lsgpu_llvm/
  LUCA_PHASE_II_PROJECT := y
  export LUCA_PHASE_II_PROJECT
endif
LSCC := ${LUCA_LLVM}/bin/htcc
ifeq ($(wildcard ${LSCC}),)
  LSCC := ${LUCA_LLVM}/bin/lscc
endif

ifeq ($(wildcard ${LSCC}),)
  ifneq ($(target-lscc-y)$(target-lscc-libso-y)$(target-lscc-liba-y),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found lscc with target lscc not empty, but __IGNORE_NOTFOUND_ERROR__)
    else
      $(error Not found lscc with target lscc not empty, install LUCA first)
    endif
  endif
endif

ifneq ($(wildcard ${LUCA_ROOT}),)
  GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
  LUCA_VERSION_RAW := $(shell echo ${LUCA_ROOT} | ${GREP} | head -1)
  LUCA_VERSION_MAJOR := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$1}')
  LUCA_VERSION_MINOR := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$2}')
  LUCA_VERSION_PATCH := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$3}')

  HAVE_LUCA := y
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

ifeq (${LUCA_PHASE_II_PROJECT},y)
  $(call check_file_and_def,${LUCA_ROOT}/include/lcdnn/lcdnn.h,HAVE_LCDNN)
  $(call check_file_and_def,${LUCA_ROOT}/include/lcfile.h,HAVE_LCFILE)
else
  $(call check_file_and_def,${LUCA_ROOT}/include/hcdnn/hcdnn.h,HAVE_LCDNN)
  $(call check_file_and_def,${LUCA_ROOT}/include/hcfile.h,HAVE_LCFILE)
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
