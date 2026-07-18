# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output defintions:
# - HAVE_NOTCURSES_H=[y|n]
# - HAVE_NCPLAYER=[y]
#
ifndef _NOTCURSES_MK
_NOTCURSES_MK = 1

include define.mk

$(call check_file_and_def,/usr/include/notcurses/notcurses.h,HAVE_NOTCURSES_H)
$(call find_cmd_and_def,ncplayer)

endif
