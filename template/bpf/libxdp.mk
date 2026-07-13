# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBXDP=[y]
# - HAVE_LIBXDP_H=[y]
# - HAVE_LIBXDP_XSK_H=[y]
#
ifndef _BPF_LIBXDP_MK
_BPF_LIBXDP_MK = 1

include define.mk

LIBXDP_H := /usr/include/xdp/libxdp.h
XSK_H := /usr/include/xdp/xsk.h

$(call check_file_and_def,${LIBXDP_H},HAVE_LIBXDP)
$(call check_file_and_def,${LIBXDP_H},HAVE_LIBXDP_H)
$(call check_file_and_def,${XSK_H},HAVE_LIBXDP_XSK_H)

endif
