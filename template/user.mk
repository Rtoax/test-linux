# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2025 Rong Tao
_USER = 1

UID := $(shell id -u)

CFLAGS += -DUID=${UID}
