# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LIBUUID_HDR=[/usr/include/uuid/uuid.h]
# - HAVE_LIBUUID=[y|n]
#
ifndef _UTIL_LINUX_MK
_UTIL_LINUX_MK = 1

include shell.mk
include define.mk

$(call find_cmd_and_def,numactl)

LIBUUID_HDR := /usr/include/uuid/uuid.h

$(call check_file_and_def,${LIBUUID_HDR},HAVE_LIBUUID)

export HAVE_LIBUUID := y

endif # end of _UTIL_LINUX_MK
