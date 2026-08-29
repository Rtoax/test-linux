# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LM_SENSORS=[/usr/bin/tmux]
# - HAVE_LM_SENSORS=[y|n]
#
ifndef _LM_SENSORS_MK
_LM_SENSORS_MK = 1

include define.mk

$(call find_cmd_and_def,sensors,lm_sensors)

endif # end of _LM_SENSORS_MK
