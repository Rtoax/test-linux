# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_PYTHON_SPHINX=[y|n]
# - SPHINX_BUILD=[/usr/bin/sphinx-build]
#
ifndef _PYTHON_SPHINX_MK
_PYTHON_SPHINX_MK = 1

include python/module.mk

SPHINX_BUILD := $(shell which sphinx-build 2>/dev/null || true)

export HAVE_PYTHON_SPHINX := $(call python_has_module,sphinx)

ifdef DEBUG
  $(info HAVE_PYTHON_SPHINX = ${HAVE_PYTHON_SPHINX})
  $(info SPHINX_BUILD = ${SPHINX_BUILD})
endif

endif
