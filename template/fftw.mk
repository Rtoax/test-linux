# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_FFTW=[y|n]
#
ifndef _FFTW_MK
_FFTW_MK = 1

include shell.mk
include define.mk

FFTW_HDR := /usr/include/fftw3.h

$(call check_file_and_def,${FFTW_HDR},HAVE_FFTW)

endif # end of _FFTW_MK
