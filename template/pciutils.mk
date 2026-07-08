# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - LSPCI=[/usr/bin/lspci]
# - HAVE_LSPCI=[y|n]
# - HAVE_PCIUTILS=[y|n]
# - HAVE_PCIUTILS_PCI_H=[y|n]
#
# Functions:
# - find_pci_device()=[y|n]
#
ifndef _PCIUTILS_MK
_PCIUTILS_MK = 1

include arch.mk
include dir.mk
include shell.mk
include define.mk

$(call find_cmd_and_def,lspci)

ifeq (${LSPCI},)
  $(warning Not found pciutils, please install first)
  export HAVE_PCIUTILS := n
else
  export HAVE_PCIUTILS := y
  ifneq ($(wildcard /usr/include/pci/pci.h),)
    # Fedora
    $(call check_file_and_def,/usr/include/pci/pci.h,HAVE_PCIUTILS_PCI_H)
  else ifneq ($(wildcard /usr/include/${CPU_ARCH}-linux-gnu/pci/pci.h),)
    # Ubuntu
    $(call check_file_and_def,/usr/include/${CPU_ARCH}-linux-gnu/pci/pci.h,HAVE_PCIUTILS_PCI_H)
  endif
endif # end of found PCIUTILS

# Find pci device with Vendor ID and Device ID
# $1: Vendor ID, Nvidia 10DE for example
# $2: Device ID, Nvidia GB10 2e12 for example
# return 'y' if found, 'n' if not found
define find_pci_device
$(shell if [[ -z $$(${LSPCI} -d ${1}:${2} 2>/dev/null) ]]; then echo n; \
	else echo y; fi)
endef

ifdef DEBUG
  $(info HAVE_PCIUTILS = ${HAVE_PCIUTILS})
  $(info HAVE_PCIUTILS_PCI_H = ${HAVE_PCIUTILS_PCI_H})
endif

endif # end of _PCIUTILS_MK
