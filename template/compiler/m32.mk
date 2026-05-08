# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_M32_MK
_COMPILER_M32_MK = 1

include compiler/check.mk

cachefile := ${TOPDIR}/template/compiler/.m32.mk.cache

ifneq ($(wildcard ${cachefile}),)
  include ${cachefile}
else
include bits/mk-cache.mk

CC_M32 := $(findstring y,$(call check_compiler_option,$(CC),-m32))
feature-m32 := $(findstring y,$(call check_compiler_option_S,$(CC),-m32))

$(call mk_cache_var,CC_M32,${cachefile})
$(call mk_cache_var,feature-m32,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC_M32: ${CC_M32})
  $(info feature-m32 ${feature-m32})
endif

endif
