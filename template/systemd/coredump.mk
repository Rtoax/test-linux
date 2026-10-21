# SPDX-License-Identifier: GPL-3.0
#
# Definitions:
# - HAVE_COREDUMPCTL=[y|n]
#
ifndef _SYSTEMD_COREDUMP_MK
_SYSTEMD_COREDUMP_MK = 1

include define.mk

$(call find_cmd_and_def,coredumpctl)

endif # end of _SYSTEMD_COREDUMP_MK
