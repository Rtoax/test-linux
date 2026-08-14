# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
ifndef _COMPILER_SANITIZER_MK
_COMPILER_SANITIZER_MK = 1

include dir.mk
include compiler/check.mk
include file.mk

cachefile := ${TOPDIR}/template/compiler/.sanitizer.mk.cache
origfile := ${TOPDIR}/template/compiler/sanitizer.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

include bits/mk-cache.mk

$(call make_gen_cachefile,${cachefile},${origfile})

CC_lasan := $(findstring y,$(call compiler_support_option_link,$(CC),-lasan))
CC_ltsan := $(findstring y,$(call compiler_support_option_link,$(CC),-ltsan))
CC_lubsan := $(findstring y,$(call compiler_support_option_link,$(CC),-lubsan))

$(call make_append_var_to_file,CC_lasan,${cachefile})
$(call make_append_var_to_file,CC_ltsan,${cachefile})
$(call make_append_var_to_file,CC_lubsan,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})

  $(info CC_lasan: ${CC_lasan})
  $(info CC_ltsan: ${CC_ltsan})
  $(info CC_lubsan: ${CC_lubsan})
endif

endif
