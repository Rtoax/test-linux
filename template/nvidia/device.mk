# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_NVIDIA_GPU=[y|n]
#
ifndef _NVIDIA_DEVICE_MK
_NVIDIA_DEVICE_MK = 1

# https://admin.pci-ids.ucw.cz/read/PC/10DE
NVIDIA_PCI_VENDOR_ID := 10DE

HAVE_NVIDIA_GPU := n

# Your system has Nvidia GPU card
ifneq ($(shell lspci -d ${NVIDIA_PCI_VENDOR_ID}:*),)
  HAVE_NVIDIA_GPU := y
endif

ifdef DEBUG
  $(info HAVE_NVIDIA_GPU = ${HAVE_NVIDIA_GPU})
endif

export HAVE_NVIDIA_GPU

endif
