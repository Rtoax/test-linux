# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_PYTHON_SPHINX=[y|n]
#
ifndef _PYTHON_SPHINX_MK
_PYTHON_SPHINX_MK = 1

include python/module.mk

export HAVE_PYTHON_SPHINX := $(call python_has_module,sphinx)

ifdef DEBUG
  $(info HAVE_PYTHON_SPHINX = ${HAVE_PYTHON_SPHINX})
endif

endif
