# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - HAVE_LUCA=[y]
# - HAVE_LCDNN=[y]
# - HAVE_LCFILE=[y]
# - HAVE_LCPTI=[y]
# - HAVE_LSVPU=[y]
#
# - LUCA_ROOT=[/opt/luca]
# - LUCA_LLVM=${LUCA_ROOT}/lsgpu_llvm/
#
# - LSCC=
# - LUCA_VERSION_MAJOR=
# - LUCA_VERSION_MINOR=
# - LUCA_VERSION_PATCH=
#
ifndef _CESTC_LUCA_MK
_CESTC_LUCA_MK = 1

include define.mk

LUCA_ROOT := /opt/luca
LUCA_ROOT := $(shell realpath ${LUCA_ROOT} 2>/dev/null || true)
LUCA_CU_BRIDGE := ${LUCA_ROOT}/tools/cu-bridge/include/
LUCA_LLVM := ${LUCA_ROOT}/lsgpu_llvm/
LSCC := ${LUCA_LLVM}/bin/lscc

LUCA_VERSION_MAJOR :=
LUCA_VERSION_MINOR :=
LUCA_VERSION_PATCH :=

ifeq ($(wildcard ${LUCA_ROOT}),)
  $(warning Not found LUCA_ROOT="${LUCA_ROOT}", please install LUCA SDK!)
else # Found LUCA

export HAVE_LUCA := y

GREP := grep -Eo '[0-9]+\.[0-9]+\.[0-9]+'
LUCA_VERSION_RAW := $(shell echo ${LUCA_ROOT} | ${GREP} | head -1)
LUCA_VERSION_MAJOR := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$1}')
LUCA_VERSION_MINOR := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$2}')
LUCA_VERSION_PATCH := $(shell echo ${LUCA_VERSION_RAW} | awk -F '.' '{print $$3}')

# Note: During the LUCA development process, the path and file name changed.
ifeq ($(wildcard ${LUCA_LLVM}),)
  $(error Not found ${LUCA_LLVM}, you need to install newest LUCA)
endif

$(call check_file_and_def,${LUCA_ROOT}/include/lcdnn/lcdnn.h,HAVE_LCDNN)
$(call check_file_and_def,${LUCA_ROOT}/include/lcfile.h,HAVE_LCFILE)
$(call check_file_and_def,${LUCA_ROOT}/include/lcpti/lcpti.h,HAVE_LCPTI)
$(call check_file_and_def,${LUCA_ROOT}/include/lcr/lc_vpu_api.h,HAVE_LSVPU)

export LUCA_ROOT
export LUCA_LLVM
export LSCC
export LUCA_VERSION_MAJOR LUCA_VERSION_MINOR LUCA_VERSION_PATCH

endif # End of found LUCA

ifdef DEBUG
  $(info LUCA_ROOT = ${LUCA_ROOT})
  $(info LSCC = ${LSCC})
  $(info LUCA_VERSION_RAW = ${LUCA_VERSION_RAW})
  $(info LUCA_VERSION_MAJOR = ${LUCA_VERSION_MAJOR})
  $(info LUCA_VERSION_MINOR = ${LUCA_VERSION_MINOR})
  $(info LUCA_VERSION_PATCH = ${LUCA_VERSION_PATCH})
endif

endif # End of _CESTC_LUCA_MK
