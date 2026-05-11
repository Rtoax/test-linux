#!/bin/bash
# UEFI Boot Manager
# see also efivar(1)
set -e

# Displaying the current settings
# - if on physical machine, read from /sys/firmware/efi/efivars/Bootxxx
# - if on virtual machine, from nvram like /var/lib/libvirt/qemu/nvram/fedora.qcow2
sudo efibootmgr
sudo efibootmgr -v
# read from efivars
ls /sys/firmware/efi/efivars/Boot*
