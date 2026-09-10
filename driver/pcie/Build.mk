include pciutils.mk

subdir-${HAVE_PCIUTILS_HDR} += config-space
subdir-${HAVE_PCIUTILS} += pciutils
subdir-y += modules

prog-y += info.sh
prog-y += find.sh
