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

localhost_files=( $(sudo find /boot/efi/EFI/BOOT/ -type f) )

dev_loop=
mnt_point=$(mktemp -u mnt-XXXXXX)

declare -a files

# vfat, msdos
overhead=256
blocksize=2048
total_size=$(( ${overhead} * ${blocksize} ))

# $1 - block size
# $2 - size
roundup()
{
	local blksize=$1
	local size=$2
	local diff
	# Round up to block size
	diff=$(( ${size} % ${blksize} ))
	size=$(( ${size} + ${blksize} - ${diff} ))
	echo ${size}
}

add_file() {
	local f=$1
	local sz

	[[ -z ${f} ]] && echo "ERROR: need input file" && exit 1
	[[ ! -e ${f} ]] && echo "ERROR: ${f} is not exist." && exit 1
	files+=( $f )

	sz=$(stat --printf %s ${f})
	sz=$(roundup ${blocksize} ${sz})

	total_size=$(( ${total_size} + ${sz} ))
}

__usage__() {
	echo -e "
${ANSI_BOLD}NAME${ANSI_RESET}

    $prog_name - Make efiboot image

${ANSI_BOLD}SYNOPSIS${ANSI_RESET}

    $prog_name [options]

${ANSI_BOLD}DESCRIPTION${ANSI_RESET}

${ANSI_BOLD}ARGUMENT${ANSI_RESET}

    -f, --file [FILE]  the files will be copied into image::EFI/BOOT/ directory
                       (may be listed multiple times)
                       for example: -f path/to/BOOTX64.EFI

    -h, --help         show this help information

${ANSI_BOLD}SEE ALSO${ANSI_RESET}

    mkfs.msdos(8)

" | more
	exit ${1-0}
}

__main__() {
	TEMP=$(getopt \
		--options f:h \
		--long file: \
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
		-f|--file)
			shift
			add_file $1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z "${files[@]}" ]]; then
		echo "ERROR: Must specify -f, --file [FILE]"
		exit 1
	fi
}

mkefiboot() {
	local tmp
	local efibootimg=efiboot.img

	truncate --size ${total_size} ${efibootimg}

	sudo losetup --find --show ${efibootimg}
	sudo udevadm settle --timeout 300

	# Found which loop device used by this image
	tmp=$(sudo losetup -j ${efibootimg})
	dev_loop=${tmp%%:*}

	sudo mkfs.msdos -n ANACONDA ${dev_loop}

	mkdir ${mnt_point}
	sudo mount -o shortname=winnt,umask=0077 ${dev_loop} ${mnt_point}

	sudo mkdir -p ${mnt_point}/EFI/BOOT/

	sudo cp -R -L --preserve=timestamps ${files[@]} ${mnt_point}/EFI/BOOT

	sudo df ${mnt_point}
	sudo tree ${mnt_point}
}

__main__ "$@"

clean_all() {
	# Do some clean
	sudo umount ${mnt_point} || true
	sudo rmdir ${mnt_point} || true
	sudo losetup --detach ${dev_loop} || true
}
trap clean_all EXIT

echo "Total size ${total_size} Bytes."

mkefiboot

