# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - SMARTCTL=[/usr/bin/smartctl]
# - HAVE_SMARTCTL=[y|n]
#
ifndef _SMARTCTL_MK
_SMARTCTL_MK = 1

include define.mk

$(call find_cmd_and_def,smartctl)

HAVE_SMARTMONTOOLS := ${HAVE_SMARTCTL}

ifdef DEBUG
  $(info HAVE_SMARTMONTOOLS = ${HAVE_SMARTMONTOOLS})
endif

endif # end of _SMARTCTL_MK
