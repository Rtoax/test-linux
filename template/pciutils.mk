# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LSPCI=[/usr/bin/lspci]
# - HAVE_LSPCI=[y|n]
# - HAVE_PCIUTILS=[y|n]
# - HAVE_PCIUTILS_PCI_H=[y|n]
#
ifndef _PCIUTILS_MK
_PCIUTILS_MK = 1

include dir.mk
include shell.mk
include define.mk

$(call find_cmd_and_def,lspci)

PCIUTILS_PCI_H := /usr/include/pci/pci.h

ifeq (${LSPCI},)
  $(warning Not found pciutils, please install first)
  export HAVE_PCIUTILS := n
else
  $(call check_file_and_def,${PCIUTILS_PCI_H},HAVE_PCIUTILS_PCI_H)
  export HAVE_PCIUTILS := y
endif # end of found PCIUTILS

ifdef DEBUG
  $(info HAVE_PCIUTILS = ${HAVE_PCIUTILS})
  $(info HAVE_PCIUTILS_PCI_H = ${HAVE_PCIUTILS_PCI_H})
endif

endif # end of _PCIUTILS_MK
