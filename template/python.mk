# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_PYTHON=[y|n]
# - PYTHON=[/usr/bin/python]
#
# Functions:
# - python_has_module()=[y|n]
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

# Check python module is installed.
# $1: module name, like: numpy
# @return: echo 'y' if exist, 'n' if not exist.
define python_has_module
$(shell if ${PYTHON} -c "import ${1}" 2>/dev/null; then echo 'y'; else echo 'n'; fi)
endef

export PYTHON

ifdef DEBUG
  $(info HAVE_PYTHON = ${HAVE_PYTHON})
  $(info PYTHON = ${PYTHON})
endif

ifneq ($(call python_has_module,os),y)
  $(error Your python ${PYTHON} not has os module)
endif

endif
