# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Definitions:
# - UEFI_BOOT=[y|n]
#
ifndef _UEFI_MK
_UEFI_MK = 1

include define.mk

$(call check_file_and_def,/sys/firmware/efi,UEFI_BOOT)

endif
