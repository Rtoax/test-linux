# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_M32_MK
_COMPILER_M32_MK = 1

include dir.mk
include compiler/check.mk
include file.mk

cachefile := ${TOPDIR}/template/compiler/.m32.mk.cache
origfile := ${TOPDIR}/template/compiler/m32.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else
include bits/mk-cache.mk

$(call make_gen_cachefile,${cachefile})

CC_SUPPORT_m32 := $(findstring y,$(call compiler_support_option_link,$(CC),-m32))

$(call make_append_var_to_file,CC_SUPPORT_m32,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC_SUPPORT_m32: ${CC_SUPPORT_m32})
endif

endif
