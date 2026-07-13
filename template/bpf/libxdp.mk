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

include define.mk

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

ifdef DEBUG
  $(info cflags-libxdp-y = ${cflags-libxdp-y})
endif

endif
