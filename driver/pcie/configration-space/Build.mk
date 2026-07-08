include helpers.mk
include pciutils.mk

target-${HAVE_PCIUTILS_PCI_H} := configuration-space
prog-${HAVE_PCIUTILS_PCI_H} := info.sh

configuration-space-objs := ${PCIE_HELPERS}
