# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_PYTORCH=[y|n]
#
ifndef _PYTHON_PYTORCH_MK
_PYTHON_PYTORCH_MK = 1

include python/module.mk

export HAVE_PYTORCH := $(call python_has_module,torch)

ifdef DEBUG
  $(info HAVE_PYTORCH = ${HAVE_PYTORCH})
endif

endif
