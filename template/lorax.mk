# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LORAX=[/usr/bin/lorax]
# - HAVE_LORAX=[y|n]
#
ifndef _LORAX_MK
_LORAX_MK = 1

include define.mk

$(call find_cmd_and_def,lorax)

endif # end of _LORAX_MK
