# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - TRACE_CMD=[/usr/bin/trace-cmd]
# - HAVE_TRACE_CMD=[y|n]
#
ifndef _TRACE_CMD_MK
_TRACE_CMD_MK = 1

include shell.mk
include define.mk

$(call find_cmd_and_def,trace-cmd)

ifeq (${TRACE_CMD},)
  $(warning Not found trace-cmd, please install first)
else

endif # end of found TRACE_CMD

endif # end of _TRACE_CMD_MK
