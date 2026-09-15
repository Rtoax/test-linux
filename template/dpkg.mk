# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - DPKG=[/usr/bin/dpkg]
# - HAVE_DPKG=[y|n]
#
ifndef _DPKG_MK
_DPKG_MK = 1

include define.mk

$(call find_cmd_and_def,dpkg)

endif # end of _DPKG_MK
