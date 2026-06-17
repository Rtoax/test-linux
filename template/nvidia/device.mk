# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_NVIDIA_GPU=[y|n]
# - HAVE_NVIDIA_GPU_GB20B_GB10=[y|n]
# - HAVE_NVIDIA_GPU_GH100_H800=[y|n]
#
# - NVIDIA_PCI_VENDOR_ID
# - NV_GB20B_GB10_PCI_DEV_ID
#
# - cflags-nvidia-device-y
#
# Refs:
# - https://admin.pci-ids.ucw.cz/read/PC/10DE
#
ifndef _NVIDIA_DEVICE_MK
_NVIDIA_DEVICE_MK = 1

include pciutils.mk

NVIDIA_PCI_VENDOR_ID := 10DE

NV_GB20B_GB10_PCI_DEV_ID := 2E12 # NVIDIA Spark DGX
NV_GH100_H800_PCI_DEV_ID := 2324

HAVE_NVIDIA_GPU := n

# Your system has Nvidia GPU card
# FIXME: not accurate, pci bridge in here too
ifneq ($(shell lspci -d ${NVIDIA_PCI_VENDOR_ID}:*),)
  HAVE_NVIDIA_GPU := y
endif

export HAVE_NVIDIA_GPU_GB20B_GB10 := $(call find_pci_device,${NVIDIA_PCI_VENDOR_ID},${NV_GB20B_GB10_PCI_DEV_ID})
export HAVE_NVIDIA_GPU_GH100_H800 := $(call find_pci_device,${NVIDIA_PCI_VENDOR_ID},${NV_GH100_H800_PCI_DEV_ID})

cflags-nvidia-device-${HAVE_NVIDIA_GPU_GB20B_GB10} += -DHAVE_NVIDIA_GPU_GB20B_GB10=1
cflags-nvidia-device-${HAVE_NVIDIA_GPU_GH100_H800} += -DHAVE_NVIDIA_GPU_GH100_H800=1

ifdef DEBUG
  $(info HAVE_NVIDIA_GPU = ${HAVE_NVIDIA_GPU})
  $(info HAVE_NVIDIA_GPU_GB20B_GB10 = ${HAVE_NVIDIA_GPU_GB20B_GB10})
  $(info HAVE_NVIDIA_GPU_GH100_H800 = ${HAVE_NVIDIA_GPU_GH100_H800})
  $(info cflags-nvidia-device-y = ${cflags-nvidia-device-y})
endif

export HAVE_NVIDIA_GPU

endif
