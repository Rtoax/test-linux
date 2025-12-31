# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025 Rong Tao
#
# Output:
# CONFIG_UID=$(id -u)
#
_USER_MK = 1

CONFIG_UID := $(shell id -u)

CFLAGS += -DCONFIG_UID=${CONFIG_UID}
