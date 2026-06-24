# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_PYTORCH=[y|n]
#
ifndef _PYTHON_PYTORCH_MK
_PYTHON_PYTORCH_MK = 1

include dir.mk
include file.mk

cachefile := ${TOPDIR}/template/python/.pytorch.mk.cache
origfile := ${TOPDIR}/template/python/pytorch.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

include python/module.mk
include bits/mk-cache.mk

HAVE_PYTORCH := $(call python_has_module,torch)

$(call mk_cache_var,HAVE_PYTORCH,${cachefile})

endif # End of cache

export HAVE_PYTORCH

ifdef DEBUG
  $(info HAVE_PYTORCH = ${HAVE_PYTORCH})
endif

endif
