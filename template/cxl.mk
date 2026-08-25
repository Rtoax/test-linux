# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Output definitions:
# HAVE_CXL_DEVICE=[y|n]
#
ifndef _CXL_MK
_CXL_MK = 1

include define.mk

$(call check_file_and_def,/sys/bus/cxl/devices,HAVE_CXL_DEVICE)

ifdef DEBUG
  $(info HAVE_CXL_DEVICE = ${HAVE_CXL_DEVICE})
endif

endif
