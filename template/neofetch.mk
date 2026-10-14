# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - NEOFETCH=[/usr/bin/neofetch]
# - HAVE_NEOFETCH=[y|n]
#
ifndef _NEOFETCH_MK
_NEOFETCH_MK = 1

include define.mk

$(call find_cmd_and_def,neofetch)

endif # end of _NEOFETCH_MK
