# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - APT=[/usr/bin/apt]
# - HAVE_APT=[y|n]
#
ifndef _APT_MK
_APT_MK = 1

include define.mk

$(call find_cmd_and_def,apt)

endif # end of _APT_MK
