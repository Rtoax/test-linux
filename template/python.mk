# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_PYTHON=[y|n]
# - PYTHON=[/usr/bin/python]
#
ifndef _PYTHON_MK
_PYTHON_MK = 1

PYTHON := $(shell which python 2>/dev/null || true)
ifeq (${PYTHON},)
  PYTHON := $(shell which python3 2>/dev/null || true)
endif

ifeq (${PYTHON},)
  $(warning "Not found python or python3")
  export HAVE_PYTHON := n
else
  export HAVE_PYTHON := y
endif

export PYTHON

ifdef DEBUG
  $(info HAVE_PYTHON = ${HAVE_PYTHON})
  $(info PYTHON = ${PYTHON})
endif

endif
