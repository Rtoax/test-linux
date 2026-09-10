include pciutils.mk

subdir-${HAVE_PCIUTILS_PCI_H} += config-space
subdir-${HAVE_PCIUTILS} += pciutils
subdir-y += modules

prog-y += info.sh
prog-y += find.sh
