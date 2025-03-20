#!/bin/bash
set -e

readonly prog=$0

BLK=blk.bin
LOOP=

verbose=
dry_run=

_eval()
{
	if [[ -z ${dry_run} ]]; then
		echo >&2 -e "\033[1;32m$@\033[m"
		eval "$@"
	else
		echo "$@"
	fi
}

mkgpt() {
	local disk=${1}

	_eval sudo parted ${disk} mklabel gpt

	_eval sudo parted ${disk} mkpart primary fat32 0 64M --align minimal
	_eval sudo parted ${disk} mkpart logical ext4 64M 96M --align minimal
	_eval sudo parted ${disk} mkpart extended ext4 96M 128M --align minimal
	_eval sudo parted ${disk} mkpart extended xfs 128M 512M --align minimal

	# if use /dev/loop, partition with 'p' suffix
	P=
	if [[ ${disk:0:9} == /dev/loop ]]; then
		P=p
	fi
	_eval sudo mkfs.fat -n TL-FAT ${disk}${P}1
	_eval sudo mkfs.ext4 -L TL-EXT4 -T largefile ${disk}${P}2
	_eval sudo mkfs.ext4 -L TL-EXT4 -T largefile ${disk}${P}3
	_eval sudo mkfs.xfs -L TL-XFS ${disk}${P}4

	_eval sleep 1
	_eval lsblk -o +fstype,label,uuid
}

__usage__()
{
	echo -e "
${prog} [options] [--dry-run]

-h, --help         show this help information
-u, --dry-run      only show commands
" | more

	exit ${1-0}
}

# __main__
GETOPT_ARGS=$(getopt \
	--options hvu \
	--long help \
	--long verbose \
	--long dry-run \
	-n ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$GETOPT_ARGS"

while true; do
	case $1 in
	-h|--help)
		shift
		__usage__
		;;
	-v|--verbose)
		shift
		verbose=YES
		set -x
		;;
	-u|--dry-run)
		shift
		dry_run=YES
		;;
	--)
		shift
		break
		;;
	esac
done

_eval sudo parted -ls

_eval sudo rm -f ${BLK}

_eval sudo dd if=/dev/zero of=${BLK} bs=1M count=512
LOOP=$(sudo losetup --find)
_eval sudo losetup ${LOOP} ${BLK}
_eval sudo losetup -j ${BLK}

goodbye() {
	_eval sudo losetup --detach ${LOOP}
}
trap goodbye EXIT

mkgpt ${LOOP}

