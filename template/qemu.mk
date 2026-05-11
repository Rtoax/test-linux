# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - HAVE_QEMU_NBD=[y|n]
#
ifndef _QEMU_MK
_QEMU_MK = 1

include define.mk

$(call find_cmd_and_def,qemu-nbd)

endif
