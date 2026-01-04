# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output definitions:
# - CONFIG_UID=$(id -u)
#
# Append:
# - CFLAGS
#
_USER_MK = 1

CONFIG_UID := $(shell id -u)

CFLAGS += -DCONFIG_UID=${CONFIG_UID}

export CONFIG_UID
