# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Definitions:
# - IF_NAMES=[lo eno1]
#
ifndef _NET_IF_MK
_NET_IF_MK = 1

IF_NAMES := $(shell ls /sys/class/net)

ifdef DEBUG
  $(info IF_NAMES = ${IF_NAMES})
endif

endif # end of _NET_IF_MK
