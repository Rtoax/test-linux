# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# HAVE_CXL_DEVICES=[y|n]
#
ifndef _CXL_MK
_CXL_MK = 1

include define.mk

$(call check_file_and_def,/sys/bus/cxl/devices,HAVE_CXL_DEVICES)

ifdef DEBUG
  $(info HAVE_CXL_DEVICES = ${HAVE_CXL_DEVICES})
endif

endif
