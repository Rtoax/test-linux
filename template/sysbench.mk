# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - SYSBENCH=[/usr/bin/sysbench]
# - HAVE_SYSBENCH=[y|n]
#
ifndef _SYSBENCH_MK
_SYSBENCH_MK = 1

include define.mk

$(call find_cmd_and_def,sysbench)

endif # end of _SYSBENCH_MK
