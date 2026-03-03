# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - version3_code1688()
#
ifndef _VERSION_MK
_VERSION_MK = 1

# Generate version code from major,minor,patchlevel
# $1: major, 16bits
# $2: minor, 8bits
# $3: patchlevel, 8bits
define version3_code1688
$(shell echo "$$(( (${1}<<16) + (${2}<<8) + (${3}>255?255:${3}) ))" )
endef

endif
