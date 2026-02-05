# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_HPCC=[y]
# - HAVE_HCDNN=[y]
# - HPCC_ROOT=/opt/hpcc/
# - HTCC=
# - HPCC_VERSION_MAJOR=
# - HPCC_VERSION_MINOR=
# - HPCC_VERSION_PATCH=
#
ifndef _METAX_HPCC_MK
_METAX_HPCC_MK = 1

include define.mk

HPCC_ROOT := /opt/hpcc
HPCC_ROOT := $(shell realpath ${HPCC_ROOT} 2>/dev/null || true)
HPCC_CU_BRIDGE := ${HPCC_ROOT}/tools/cu-bridge/include/
HPCC_LLVM := ${HPCC_ROOT}/htgpu_llvm/
HTCC := ${HPCC_LLVM}/bin/htcc

HPCC_VERSION_MAJOR :=
HPCC_VERSION_MINOR :=
HPCC_VERSION_PATCH :=

ifeq ($(wildcard ${HPCC_ROOT}),)
  $(warning Not found HPCC_ROOT="${HPCC_ROOT}", please include HPCC SDK!)
else # Found HPCC
GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
HPCC_VERSION_RAW := $(shell echo ${HPCC_ROOT} | ${GREP} | head -1)
HPCC_VERSION_MAJOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$1}')
HPCC_VERSION_MINOR := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$2}')
HPCC_VERSION_PATCH := $(shell echo ${HPCC_VERSION_RAW} | awk -F '.' '{print $$3}')

export HAVE_HPCC := y

$(call check_file_and_def,${HPCC_ROOT}/include/hcdnn/hcdnn.h,HAVE_HCDNN)

export HPCC_ROOT
export HPCC_LLVM
export HTCC
export HPCC_VERSION_MAJOR HPCC_VERSION_MINOR HPCC_VERSION_PATCH

endif # End of found HPCC

ifdef DEBUG
  $(info HAVE_HPCC = ${HAVE_HPCC})
  $(info HPCC_ROOT = ${HPCC_ROOT})
  $(info HTCC = ${HTCC})
  $(info HPCC_VERSION_RAW = ${HPCC_VERSION_RAW})
  $(info HPCC_VERSION_MAJOR = ${HPCC_VERSION_MAJOR})
  $(info HPCC_VERSION_MINOR = ${HPCC_VERSION_MINOR})
  $(info HPCC_VERSION_PATCH = ${HPCC_VERSION_PATCH})
endif

endif
