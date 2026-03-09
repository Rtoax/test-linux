# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_LIBXDP=[y]
#
ifndef _BPF_LIBXDP_MK
_BPF_LIBXDP_MK = 1

include define.mk

LIBXDP_H := /usr/include/xdp/libxdp.h

$(call check_file_and_def,${LIBXDP_H},HAVE_LIBXDP)

ifdef DEBUG
  $(info HAVE_LIBXDP = ${HAVE_LIBXDP})
endif

endif
