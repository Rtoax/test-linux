# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBXDP=[y]
# - HAVE_LIBXDP_H=[y]
# - HAVE_LIBXDP_XSK_H=[y]
#
# - cflags-libxdp-y=
#
ifndef _BPF_LIBXDP_MK
_BPF_LIBXDP_MK = 1

include dir.mk
include file.mk

cachefile := ${TOPDIR}/template/bpf/.libxdp.mk.cache
origfile := ${TOPDIR}/template/bpf/libxdp.mk

ifeq ($(call is_newer,${cachefile},${origfile}),y)
  include ${cachefile}
else

include define.mk
include bits/mk-cache.mk

$(call make_gen_cachefile,${cachefile})

LIBXDP_H := /usr/include/xdp/libxdp.h
XSK_H := /usr/include/xdp/xsk.h
cflags-libxdp-y :=

$(call check_file_and_def,${LIBXDP_H},HAVE_LIBXDP)
$(call check_file_and_def,${LIBXDP_H},HAVE_LIBXDP_H)
$(call check_file_and_def,${XSK_H},HAVE_LIBXDP_XSK_H)

ifneq (${HAVE_LIBXDP},)
  cflags-libxdp-y += -DHAVE_LIBXDP=1
endif
ifneq (${HAVE_LIBXDP_H},)
  cflags-libxdp-y += -DHAVE_LIBXDP_H=1
endif
ifneq (${HAVE_LIBXDP_XSK_H},)
  cflags-libxdp-y += -DHAVE_LIBXDP_XSK_H=1
endif

$(call make_append_var_to_file,HAVE_LIBXDP,${cachefile})
$(call make_append_var_to_file,HAVE_LIBXDP_H,${cachefile})
$(call make_append_var_to_file,HAVE_LIBXDP_XSK_H,${cachefile})
$(call make_append_var_to_file,cflags-libxdp-y,${cachefile})

endif # End of cachefile

ifdef DEBUG
  $(info cflags-libxdp-y = ${cflags-libxdp-y})
endif

endif
