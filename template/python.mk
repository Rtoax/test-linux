# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - PYTHON=
#
_PYTHON = 1

PYTHON := $(shell which python 2>/dev/null || true)
ifeq (${PYTHON},)
  PYTHON := $(shell which python3 2>/dev/null || true)
endif
ifeq (${PYTHON},)
  $(error "Not found python or python3")
endif

export PYTHON

ifdef DEBUG
  $(info PYTHON = ${PYTHON})
endif
