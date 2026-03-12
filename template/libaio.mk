# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_LIBAIO=[y|n]
#
ifndef _LIBAIO_MK
_LIBAIO_MK = 1

include define.mk

LIBAIO_HDR := /usr/include/libaio.h

$(call check_file_and_def,${LIBAIO_HDR},HAVE_LIBAIO)

endif # end of _LIBAIO_MK
