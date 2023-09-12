#!/bin/bash

# ref: https://docs.kernel.org/filesystems/efivarfs.html
mnt_efivarfs() {
	sudo umount /sys/firmware/efi/efivars
	sudo mount -t efivarfs none /sys/firmware/efi/efivars
}

efi_var_list() {
	efivar -l
}
