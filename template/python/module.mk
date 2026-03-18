# SPDX-License-Identifier: GPL-3.0
#
# Functions:
# - python_has_module()=[y|n]
#
ifndef _PYTHON_MODULE_MK
_PYTHON_MODULE_MK = 1

include python/python.mk

# Check python module is installed.
# $1: module name, like: numpy
# @return: echo 'y' if exist, 'n' if not exist.
define python_has_module
$(shell if ${PYTHON} -c "import ${1}" 2>/dev/null; then echo 'y'; else echo 'n'; fi)
endef

ifneq ($(call python_has_module,os),y)
  $(error Your python ${PYTHON} not has os module)
endif

endif
