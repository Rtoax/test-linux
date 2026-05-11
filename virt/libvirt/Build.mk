include libvirt.mk

subdir-${HAVE_VIRSH} += virsh

target-prog-y += capabilities.sh
