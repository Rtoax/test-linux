# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - CC_SUPPORT_m32=[y]
# - CC_MACHINE=[x86_64-linux-gnu]
# - CC_MACHINE_CFLAGS=[-march=native]
#
ifndef _COMPILER_MACHINE_MK
_COMPILER_MACHINE_MK = 1

include dir.mk
include compiler/check.mk
include file.mk

cachefile := ${TOPDIR}/template/compiler/.machine.mk.cache
origfile := ${TOPDIR}/template/compiler/machine.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else
include bits/mk-cache.mk

$(call make_gen_cachefile,${cachefile},${origfile})

CC_SUPPORT_m32 := $(findstring y,$(call compiler_support_option_link,$(CC),-m32))
CC_MACHINE := $(shell ${CC} -dumpmachine)

ifeq ($(shell uname -m),ppc64le)
  # Note: ‘-m64’ requires a PowerPC64 cpu
  CC_MACHINE_CFLAGS := -mcpu=native -m64
else
  CC_MACHINE_CFLAGS := -march=native
endif

$(call make_append_var_to_file,CC_SUPPORT_m32,${cachefile})
$(call make_append_var_to_file,CC_MACHINE,${cachefile})
$(call make_append_var_to_file,CC_MACHINE_CFLAGS,${cachefile})

endif # end of cache file exist

ifdef DEBUG
  $(info CC: ${CC})
  $(info CC_SUPPORT_m32: ${CC_SUPPORT_m32})
  $(info CC_MACHINE: ${CC_MACHINE})
  $(info CC_MACHINE_CFLAGS: ${CC_MACHINE_CFLAGS})
endif

endif
