# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - FASTFETCH=[/usr/bin/fastfetch]
# - HAVE_FASTFETCH=[y|n]
#
ifndef _FASTFETCH_MK
_FASTFETCH_MK = 1

include define.mk

$(call find_cmd_and_def,fastfetch)

endif # end of _FASTFETCH_MK
