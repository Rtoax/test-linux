# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - TPUT=[/usr/bin/tput]
# - HAVE_NCURSES=[y|n]
# - HAVE_NCURSES_H=[y|n]
# - ncurses-ldflags=
# - ncurses-cflags=
#
ifndef _NCURSES_MK
_NCURSES_MK = 1

include define.mk

$(call find_cmd_and_def,tput,ncurses)
$(call check_file_and_def,/usr/include/ncurses.h,HAVE_NCURSES_H)

ncurses-cflags += $(shell pkg-config ncurses --cflags)
ncurses-ldflags += $(shell pkg-config ncurses --libs)

ifdef DEBUG
  $(info ncurses-cflags = ${ncurses-cflags})
  $(info ncurses-ldflags = ${ncurses-ldflags})
endif

endif
