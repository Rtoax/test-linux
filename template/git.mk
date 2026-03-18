# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - GIT_TOPDIR=
# - GIT_CONFIG_CORE_HOOKSPATH=
#
ifndef _GIT_MK
_GIT_MK = 1

include dir.mk

GIT_TOPDIR := $(shell git rev-parse --show-toplevel 2>/dev/null || :)

GIT_CONFIG_CORE_HOOKSPATH := $(shell git config get core.hooksPath 2>/dev/null \
	|| git config core.hooksPath 2>/dev/null \
	|| echo "UnsupportGetHooks")

endif
