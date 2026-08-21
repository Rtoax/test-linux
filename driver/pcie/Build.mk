include pciutils.mk

subdir-${HAVE_PCIUTILS_PCI_H} += configration-space
subdir-y += modules
subdir-y += pciutils

prog-y += info.sh
prog-y += find.sh
