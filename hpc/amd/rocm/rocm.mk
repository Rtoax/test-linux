# SPDX-License-Identifier: GPL-3.0
_ROCm = 1

HIPCC := $(shell which hipcc 2>/dev/null)

HAVE_HIP := 1
export HIPCC HAVE_HIP

ifdef DEBUG
  ifneq (${HIPCC},)
    $(info $(shell ${HIPCC} --version))
  endif
  $(info HIPCC = ${HIPCC})
endif
