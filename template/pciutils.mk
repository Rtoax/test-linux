# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LSPCI=[lspci]
# - HAVE_PCIUTILS=[y|n]
# - HAVE_PCIUTILS_PCI_H=[y|n]
#
ifndef _PCIUTILS_MK
_PCIUTILS_MK = 1

include dir.mk
include shell.mk
include define.mk

LSPCI := $(shell which lspci 2>/dev/null || :)
PCIUTILS_HDR := /usr/include/pci/pci.h

ifeq (${LSPCI},)
  $(warning Not found pciutils, please install first)
  export HAVE_PCIUTILS := n
else

$(call check_file_and_def,${PCIUTILS_HDR},HAVE_PCIUTILS_PCI_H)

export LSPCI
export HAVE_PCIUTILS := y
export HAVE_PCIUTILS_PCI_H := y
endif # end of found PCIUTILS

ifdef DEBUG
  $(info LSPCI = ${LSPCI})
  $(info HAVE_PCIUTILS = ${HAVE_PCIUTILS})
  $(info HAVE_PCIUTILS_PCI_H = ${HAVE_PCIUTILS_PCI_H})
endif

endif # end of _PCIUTILS_MK
