# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_CAPSTONE=[y|n]
#
ifndef _CAPSTONE_MK
_CAPSTONE_MK = 1

include define.mk

CAPSTONE_HDR := /usr/include/capstone/capstone.h

$(call check_file_and_def,${CAPSTONE_HDR},HAVE_CAPSTONE)

endif # end of _CAPSTONE_MK
