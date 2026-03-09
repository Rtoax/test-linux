# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - LSSMI=[/usr/bin/ls-smi]
# - HAVE_LINGSPEED_GPU=[y|n]
# - HAVE_LINGSPEED_X710E=[y|n]
# - HAVE_LINGSPEED_X710M=[y|n]
# - HAVE_LINGSPEED_X710P=[y|n]
#
ifndef _CESTC_LINGSPEED_MK
_CESTC_LINGSPEED_MK = 1

# CECloud Computing Technology Co., Ltd.
# https://admin.pci-ids.ucw.cz/read/PC/20e1
CESTC_PCI_VENDOR_ID := 20e1
X710E_PCI_DEVICE_ID := 7101
X710M_PCI_DEVICE_ID := 7103
X710P_PCI_DEVICE_ID := 7104

HAVE_LINGSPEED_GPU := n
HAVE_LINGSPEED_X710E := n
HAVE_LINGSPEED_X710M := n
HAVE_LINGSPEED_X710P := n

LSSMI := $(shell which ls-smi 2>/dev/null)

ifeq ($(wildcard ${LSSMI}),)
  $(warning Not found ls-smi, please install lingspeed driver)
  LSSMI :=
endif

ifneq ($(shell lspci -d ${CESTC_PCI_VENDOR_ID}:${X710E_PCI_DEVICE_ID}),)
  export HAVE_LINGSPEED_X710E := y
  export HAVE_LINGSPEED_GPU := y
endif

ifneq ($(shell lspci -d ${CESTC_PCI_VENDOR_ID}:${X710M_PCI_DEVICE_ID}),)
  export HAVE_LINGSPEED_X710M := y
  export HAVE_LINGSPEED_GPU := y
endif

ifneq ($(shell lspci -d ${CESTC_PCI_VENDOR_ID}:${X710P_PCI_DEVICE_ID}),)
  export HAVE_LINGSPEED_X710P := y
  export HAVE_LINGSPEED_GPU := y
endif

ifdef DEBUG
  $(info LSSMI = ${LSSMI})
  $(info HAVE_LINGSPEED_GPU = ${HAVE_LINGSPEED_GPU})
  $(info HAVE_LINGSPEED_X710E = ${HAVE_LINGSPEED_X710E})
  $(info HAVE_LINGSPEED_X710M = ${HAVE_LINGSPEED_X710M})
  $(info HAVE_LINGSPEED_X710P = ${HAVE_LINGSPEED_X710P})
endif

export LSSMI

endif
