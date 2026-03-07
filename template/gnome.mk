# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
#
ifndef _GNOME_MK
export _GNOME_MK = 1

XDG_CURRENT_DESKTOP := $(shell echo $$XDG_CURRENT_DESKTOP)

ifdef DEBUG
  $(info XDG_CURRENT_DESKTOP = ${XDG_CURRENT_DESKTOP})
endif

endif # end of _GNOME_MK
