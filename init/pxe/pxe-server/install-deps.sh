#!/bin/bash

# syslinux-tftpboot for BIOS-based clients
# grub2-efi,shim-x64 for UEFI-based clients
sudo dnf install -y dhcp-server tftp-server syslinux-tftpboot grub2-efi \
		shim-x64 httpd
