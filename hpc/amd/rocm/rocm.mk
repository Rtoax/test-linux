# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Input definitions:
# - __IGNORE_NOTFOUND_ERROR__
#
# Output macros:
# - HAVE_HIP
# - HIPCC
# - HIPCONFIG

_ROCm = 1

HIPCC := $(shell which hipcc 2>/dev/null)
HIPCONFIG := $(shell which hipconfig 2>/dev/null)

ifneq ($(HIPCC),)
  HAVE_HIP := 1

  export HAVE_HIP
else
  ifneq ($(targets-hipcc),)
    ifdef __IGNORE_NOTFOUND_ERROR__
      $(warning Not found hipcc with targets-hipcc not empty, but __IGNORE_NOTFOUND_ERROR__)
    else
      $(error Not found hipcc with targets-hipcc not empty, install cuda first)
    endif
  else
    $(warning Although not found hipcc, but you don't have targets-hipcc)
  endif

  HIPCC :=
  HIPCONFIG :=
endif

export HIPCC HIPCONFIG

ifdef DEBUG
  $(info HIPCC = ${HIPCC})
  $(info HIPCONFIG = ${HIPCONFIG})
  ifneq (${HIPCC},)
    $(info $(shell ${HIPCC} --version))
  endif
  ifneq (${HIPCONFIG},)
    $(info $(shell ${HIPCONFIG} --full))
  endif
endif
