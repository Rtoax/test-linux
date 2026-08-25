# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_SS=[y]
# - SS=[/usr/bin/ss]
# - HAVE_IPROUTE=[y|n]
#
ifndef _IPROUTE_MK
_IPROUTE_MK = 1

include define.mk

$(call find_cmd_and_def,ss)

endif # end of _IPROUTE_MK
