# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_NVIDIA_GPU=[y|n]
#
# - NVIDIA_PCI_VENDOR_ID
# - NV_GB20B_PCI_DEV_ID
#
# Refs:
# - https://admin.pci-ids.ucw.cz/read/PC/10DE
#
ifndef _NVIDIA_DEVICE_MK
_NVIDIA_DEVICE_MK = 1

include pciutils.mk

NVIDIA_PCI_VENDOR_ID := 10DE

NV_GB20B_PCI_DEV_ID := 2E12 # NVIDIA Spark DGX
NV_H800_PCI_DEV_ID := 2324

HAVE_NVIDIA_GPU := n

# Your system has Nvidia GPU card
# FIXME: not accurate, pci bridge in here too
ifneq ($(shell lspci -d ${NVIDIA_PCI_VENDOR_ID}:*),)
  HAVE_NVIDIA_GPU := y
endif

HAVE_NVIDIA_GPU_GB20B := $(call find_pci_device,${NVIDIA_PCI_VENDOR_ID},${NV_GB20B_PCI_DEV_ID})
HAVE_NVIDIA_GPU_H800 := $(call find_pci_device,${NVIDIA_PCI_VENDOR_ID},${NV_H800_PCI_DEV_ID})

ifdef DEBUG
  $(info HAVE_NVIDIA_GPU = ${HAVE_NVIDIA_GPU})
  $(info HAVE_NVIDIA_GPU_GB20B = ${HAVE_NVIDIA_GPU_GB20B})
  $(info HAVE_NVIDIA_GPU_H800 = ${HAVE_NVIDIA_GPU_H800})
endif

export HAVE_NVIDIA_GPU

endif
