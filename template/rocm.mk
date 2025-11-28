# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output macros:
# - HAVE_HIP=y
# - HAVE_HIPSOLVER=y
# - HAVE_HIPBLASLT=y
# - HAVE_HIP_FP8=y
# - HAVE_RCCL=y
# - HIPCC=$(which hipcc)
# - HIPCONFIG=$(which hipconfig)
#
# Modify definitions:
# - target-hipcc-y
# - target-hipcc-liba-y
# - target-hipcc-libso-y

_ROCm = 1

include values.mk

HIPCC := $(shell which hipcc 2>/dev/null)
HIPCONFIG := $(shell which hipconfig 2>/dev/null)

ifneq ($(HIPCC),)
  HAVE_HIP := y
  export HAVE_HIP
else
  ifneq ($(target-hipcc-y)$(target-hipcc-liba-y)$(target-hipcc-libso-y),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found hipcc with target hipcc not empty, but __IGNORE_NOTFOUND_ERROR__)
    else
      $(error Not found hipcc with target hipcc not empty, install cuda first)
    endif
  else
    $(warning Although not found hipcc, but you don't have target hipcc)
  endif

  HIPCC :=
  HIPCONFIG :=
endif

# $(1) - output file name
define gen_hipcc_macro_hdr
$(Q)${HIPCC} -E -dM - </dev/null -o $(1)
endef

export HIPCC HIPCONFIG

$(call check_file_and_def,/usr/include/rccl/rccl.h,HAVE_RCCL)
$(call check_file_and_def,/usr/include/hipsolver/hipsolver.h,HAVE_HIPSOLVER)
$(call check_file_and_def,/usr/include/hipblaslt/hipblaslt.h,HAVE_HIPBLASLT)
$(call check_file_and_def,/usr/include/hip/hip_fp8.h,HAVE_HIP_FP8)

ifdef DEBUG
  $(info HAVE_HIP = ${HAVE_HIP})
  $(info HIPCC = ${HIPCC})
  $(info HIPCONFIG = ${HIPCONFIG})
  ifneq (${HIPCC},)
    $(info HIPCC: $(shell ${HIPCC} --version))
  endif
  ifneq (${HIPCONFIG},)
    $(info HIPCONFIG: $(shell ${HIPCONFIG} --full))
  endif
endif
