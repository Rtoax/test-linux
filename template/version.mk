# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Functions:
# - version3_code()
#
ifndef _VERSION_MK
_VERSION_MK = 1

# Generate version code from major,minor,patchlevel
# $1: major
# $2: minor
# $3: patchlevel
define version3_code
$(shell echo "$$(( (${1}<<16) + (${2}<<8) + (${3}>255?255:${3}) ))" )
endef

endif
