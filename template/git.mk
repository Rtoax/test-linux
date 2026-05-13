# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
#
# Output defintions:
# - GIT=[/usr/bin/git]
# - HAVE_GIT=[y|n]
#
ifndef _GIT_MK
_GIT_MK = 1

include define.mk

$(call find_cmd_and_def,git)

endif
