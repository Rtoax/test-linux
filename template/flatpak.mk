# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - FLATPAK=[/usr/bin/flatpak]
# - HAVE_FLATPAK=[y|n]
#
ifndef _FLATPAK_MK
_FLATPAK_MK = 1

include define.mk

$(call find_cmd_and_def,flatpak)

endif # end of _FLATPAK_MK
