# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - PS=[/usr/bin/ps]
# - HAVE_PS=[y|n]
#
ifndef _PROCPS_NG_MK
_PROCPS_NG_MK = 1

include define.mk

$(call find_cmd_and_def,ps)

endif # end of _PROCPS_NG_MK
