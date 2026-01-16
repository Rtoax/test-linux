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
	local boot0=$(efivar --list | grep Boot0000)

	efivar --name ${boot0} --print
}

efivar_print
