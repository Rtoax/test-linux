# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - ANACONDA=[/usr/bin/anaconda]
# - HAVE_ANACONDA=[y|n]
#
ifndef _ANACONDA_MK
_ANACONDA_MK = 1

include define.mk

$(call find_cmd_and_def,anaconda)

endif # end of _ANACONDA_MK
