# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - TPUT=[/usr/bin/tput]
# - HAVE_NCURSES=[y|n]
#
ifndef _NCURSES_MK
_NCURSES_MK = 1

include define.mk

$(call find_cmd_and_def,tput,ncurses)

endif
