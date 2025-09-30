# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
#
# Input definitions:
#
# Output macros:
# - HAVE_HIP
# - HIPCC

_ROCm = 1

HIPCC := $(shell which hipcc 2>/dev/null)
HIPCONFIG := $(shell which hipconfig 2>/dev/null)

ifneq ($(HIPCC),)
  HAVE_HIP := 1

  export HIPCC HAVE_HIP
endif

ifdef DEBUG
  ifneq (${HIPCC},)
    $(info $(shell ${HIPCC} --version))
  endif
  ifneq (${HIPCONFIG},)
    $(info $(shell ${HIPCONFIG} --full))
  endif
  $(info HIPCC = ${HIPCC})
endif
