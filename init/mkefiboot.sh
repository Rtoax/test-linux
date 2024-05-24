#!/bin/bash
# How to make efiboot.img image in Bootable ISO9660
#
# See lorax command:
#
#  $ sudo mkefiboot --label=ANACONDA /boot/efi/EFI/BOOT/ efiboot.img
#
# Python pseudocode in lorax(https://github.com/weldr/lorax):
#
#   mkefiboot(bootdir="xxx/EFI/BOOT/", outfile=efiboot.img, label=ANACONDA) {
#     mkdosimg(rootdir=None, outfile=efiboot.img, size=None, label=ANACONDA, \
#       mountargs="shortname=winnt,umask=0077", graft={'EFI/BOOT':bootdir}) {
#       mkfsargs = [ "-n", "ANACONDA" ]
#       mkfsimage("msdos", rootdir=None, outfile=efiboot.img, size=None, \
#         mountargs=mountargs, mkfsargs=mkfsargs, graft=graft) {
#           mkfsargs = [ "-n", "ANACONDA" ]
#           graft = {'EFI/BOOT':"xxx/EFI/BOOT/"}
#           ...
#         }
#     }
#   }
#
set -e

prog_name=mkefiboot

__usage__() {
	echo -e "
${ANSI_BOLD}NAME${ANSI_RESET}

    $prog_name - Make efiboot image

${ANSI_BOLD}SYNOPSIS${ANSI_RESET}

    $prog_name [options]

${ANSI_BOLD}DESCRIPTION${ANSI_RESET}

${ANSI_BOLD}ARGUMENT${ANSI_RESET}

    -h, --help         show this help information

${ANSI_BOLD}SEE ALSO${ANSI_RESET}

" | more
	exit ${1-0}
}

__main__() {
	TEMP=$(getopt \
		--options h \
		--long help \
		-n ${prog_name} -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-h|--help)
			shift
			__usage__
			;;
		--)
			shift
			break
			;;
		esac
	done
}

mkefiboot() {
	local tmp dev_loop
	local efibootimg=efiboot.img
	# vfat, msdos
	local blocksize=2048
	# FIXME: Get actual size
	local size=2M
	local mnt_point=$(mktemp -u mnt-XXXXXX)
	local files

	truncate --size ${size} ${efibootimg}

	sudo losetup --find --show ${efibootimg}
	sudo udevadm settle --timeout 300

	# Found which loop device used by this image
	tmp=$(sudo losetup -j ${efibootimg})
	dev_loop=${tmp%%:*}

	sudo mkfs.msdos -n ANACONDA ${dev_loop}

	mkdir ${mnt_point}
	sudo mount -o shortname=winnt,umask=0077 ${dev_loop} ${mnt_point}

	sudo mkdir -p ${mnt_point}/EFI/BOOT/

	# Copy files
	files=(
		$(sudo find /boot/efi/EFI/BOOT/ -type f)
	)
	sudo cp -R -L --preserve=timestamps ${files[@]} ${mnt_point}/EFI/BOOT

	sudo df ${mnt_point}
	sudo tree ${mnt_point}

	# Do some clean
	sudo umount ${mnt_point} || true
	sudo rmdir ${mnt_point}
	sudo losetup --detach ${dev_loop}
}

__main__ "$@"

mkefiboot

