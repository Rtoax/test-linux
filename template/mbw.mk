# SPDX-License-Identifier: GPL-3.0
#
# Memory BandWidth benchmark program
#
# Output definitions:
# - MBW=[/usr/bin/mbw]
# - HAVE_MBW=[y|n]
#
ifndef _MBW_MK
_MBW_MK = 1

include define.mk

$(call find_cmd_and_def,mbw)

endif # end of _MBW_MK
