#!/bin/bash
set -e
readonly prog=$0

. /etc/os-release

TARGET_ARCH=$(uname -m)
ROOTFS_DIR="${PWD}/${ID}${VERSION_ID}-${TARGET_ARCH}-rootfs"

RAW_IMAGE=
RAW_IMAGE_NEW=

verbose=
dry_run=

__usage__() {
	echo -e "
NAME
	${prog} - make rootfs for fedora liked distrobution

SYNOPSIS
	${prog} --rootfs=<DIR> [--raw=<a.raw>]

DESCRIPTION
	-r, --rootfs [DIR]      specify rootfs directory.
	    --raw [FILE NAME]   specify raw image filename

	-u, --dry-run           only show commands
	-v, --verbose           enable verbose mode.
	-h, --help              show this help information

EXAMPLES
	$ sudo ${prog} --rootfs tmp-rootfs.dir

SEE ALSO
	dnf(8)
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options r:uhv \
	--long rootfs: \
	--long raw: \
	--long dry-run \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-r | --rootfs)
		shift
		ROOTFS_DIR=$1
		shift
		;;
	--raw)
		shift
		RAW_IMAGE=$1
		if [[ -e ${RAW_IMAGE} ]]; then
			echo >&2 "WARNING: ${RAW_IMAGE} already exist."
		else
			RAW_IMAGE_NEW=YES
		fi
		shift
		;;
	-h | --help)
		shift
		__usage__
		;;
	-u | --dry-run)
		shift
		dry_run=YES
		;;
	-v | --verbose)
		shift
		verbose=YES
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ -z ${ROOTFS_DIR} ]]; then
	echo >&2 "ERROR: Must speicfy rootfs directory"
	exit 1
fi

ROOTFS_DIR=$(realpath ${ROOTFS_DIR})

if [[ ${verbose} ]]; then
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
fi

_eval()
{
	if [[ -z ${dry_run} ]]; then
		echo >&2 -e "\033[1;32mStartup: $@\033[m"
		eval "$@"
		echo >&2 -e "\033[1;33mDone: $@\033[m"
	else
		echo "$@"
	fi
}

os_dnf() {
	_eval sudo dnf --installroot=${ROOTFS_DIR} \
		--releasever=${VERSION_ID} \
		--forcearch=${TARGET_ARCH} \
		--use-host-config -y \
		"$@"
}

# TODO
chroot_cmd() {
	sudo chroot ${ROOTFS_DIR} "$@"
}

dev_nbd=
dev_uuid=
raw_create_and_mount() {
	dev_nbd=/dev/nbd0

	[[ -z ${RAW_IMAGE} ]] && return 0

	if [[ ${RAW_IMAGE} ]] && [[ ! -e ${RAW_IMAGE} ]]; then
		_eval qemu-img create -f raw ${RAW_IMAGE} 10G
	fi

	_eval sudo modprobe nbd max_part=16 || true
	_eval sudo qemu-nbd --connect ${dev_nbd} ${RAW_IMAGE} -f raw

	# Make fs if new create
	[[ ${RAW_IMAGE_NEW} ]] && _eval sudo mkfs.xfs ${dev_nbd}

	if [[ ${dry_run} ]]; then
		dev_uuid=$(uuid)
	else
		dev_uuid=$(sudo lsblk -o uuid ${dev_nbd} | grep -v UUID)
	fi
	_eval sudo mount ${dev_nbd} ${ROOTFS_DIR}
}

raw_unmount() {
	[[ -z ${RAW_IMAGE} ]] && return 0

	_eval sudo umount ${ROOTFS_DIR}
	_eval sudo qemu-nbd --disconnect ${dev_nbd}
	_eval sudo rmmod nbd || true
}

_eval sudo mkdir -p ${ROOTFS_DIR}

if [[ ${RAW_IMAGE} ]]; then
	raw_create_and_mount
fi

os_dnf group install development-tools
os_dnf install dnf make sudo rpm vim glibc-static

if [[ ${RAW_IMAGE} ]]; then
	raw_unmount
fi

echo >&2 -e "\033[32m"
echo >&2 "${ID} ${VERSION_ID} rootfs for ${TARGET_ARCH} has been created at ${ROOTFS_DIR}"
[[ ${RAW_IMAGE} ]] && echo >&2 "UUID=${dev_uuid}"
echo >&2 -e "\033[0m"
