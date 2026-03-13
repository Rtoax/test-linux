#!/bin/bash
set -e

# ref: https://docs.kernel.org/filesystems/efivarfs.html
mnt_efivarfs() {
	sudo umount /sys/firmware/efi/efivars
	sudo mount -t efivarfs none /sys/firmware/efi/efivars
}

efivar_list() {
	efivar --list
}

efivar_print() {
	local boot
	for boot in $(efivar --list | grep -E 'Boot[0-9]+')
	do
		efivar --name ${boot} --print
	done
}

efivar_print
