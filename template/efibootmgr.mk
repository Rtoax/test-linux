# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - HAVE_EFIBOOTMGR=[y|n]
# - EFIBOOTMGR=[/usr/bin/efibootmgr]
#
ifndef _EFIBOOTMGR_MK
_EFIBOOTMGR_MK = 1

include define.mk

$(call find_cmd_and_def,efibootmgr)

endif
