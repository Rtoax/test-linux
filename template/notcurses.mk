# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output defintions:
# - HAVE_NOTCURSES_H=[y|n]
#
ifndef _NOTCURSES_MK
_NOTCURSES_MK = 1

include define.mk

$(call check_file_and_def,/usr/include/notcurses/notcurses.h,HAVE_NOTCURSES_H)

endif
