include libvirt.mk

subdir-${HAVE_VIRSH} += virsh

prog-y += capabilities.sh
