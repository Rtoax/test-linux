#!/bin/bash
set -e

readonly prog=$0

BLK=blk.bin
# see parted(8)
PARTITION_TYPE=gpt
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

mkpartitions() {
	local disk=${1}

	_eval sudo parted ${disk} mklabel ${PARTITION_TYPE}

	_eval sudo parted ${disk} mkpart primary fat32 0 64M --align minimal
	# mbr/msdos only support primary/extended
	if [[ ${PARTITION_TYPE} != msdos ]]; then
		_eval sudo parted ${disk} mkpart logical ext4 64M 96M --align minimal
		_eval sudo parted ${disk} mkpart extended ext4 96M 128M --align minimal
		_eval sudo parted ${disk} mkpart extended xfs 128M 512M --align minimal
	else
		_eval sudo parted ${disk} mkpart primary ext4 64M 96M --align minimal
		_eval sudo parted ${disk} mkpart primary ext4 96M 128M --align minimal
		_eval sudo parted ${disk} mkpart primary xfs 128M 512M --align minimal
	fi

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
${prog} --type=[gpt|mbr] [--dry-run]

-n, --name [STR]   specify blk name, default: ${BLK}
-t, --type [gpt|mbr]
                   specify partition type, support: \"gpt\", \"mbr\", default: \"${PARTITION_TYPE}\"

-h, --help         show this help information
-v, --verbose      show detail during running
-u, --dry-run      only show commands
" | more

	exit ${1-0}
}

# __main__
GETOPT_ARGS=$(getopt \
	--options n:t:hvu \
	--long name: \
	--long type: \
	--long help \
	--long verbose \
	--long dry-run \
	-n ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$GETOPT_ARGS"

while true; do
	case $1 in
	-n|--name)
		shift
		BLK=$1
		shift
		;;
	-t|--type)
		shift
		PARTITION_TYPE=$1
		if ! [[ " msdos gpt mbr " =~ " $PARTITION_TYPE " ]]; then
			echo >&2 "ERROR: not support partition type $PARTITION_TYPE"
			exit 1
		fi
		[[ ${PARTITION_TYPE} == mbr ]] && PARTITION_TYPE=msdos
		shift
		;;
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

mkpartitions ${LOOP}

