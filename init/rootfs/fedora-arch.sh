#!/bin/bash
# Wrote by Rong Tao
set -e
readonly prog=$0

. /etc/os-release

TARGET_ARCH=$(uname -m)
ROOTFS_DIR=

IMAGE=
IMAGE_TYPE=
IMAGE_NEW=

declare -a pkgs
pkgs+=( dnf make sudo rpm vim glibc-static hostname iproute pciutils
	NetworkManager )

verbose=
dry_run=

__usage__() {
	echo -e "
NAME
	${prog} - make rootfs for fedora liked distrobution

SYNOPSIS
	${prog} --rootfs=<DIR> [--image=<vm.raw|vm.qcow2>]

DESCRIPTION
	-r, --rootfs [DIR]      specify rootfs directory.
	    --image [NAME]      specify image filename

	-i, --install [PKG]     install package, (may be listed multiple times)

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

TEMP_ARGS=$(getopt --options r:i:uhv \
	--long rootfs: \
	--long image: \
	--long install: \
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
	--image)
		shift
		IMAGE=$1
		IMAGE_TYPE=${IMAGE##*.}
		if ! [[ " raw qcow2 " =~ " ${IMAGE_TYPE} " ]]; then
			echo >&2 "ERROR: ${IMAGE} is not raw or qcow2."
			exit 1
		fi
		if [[ -e ${IMAGE} ]]; then
			echo >&2 "WARNING: ${IMAGE} already exist."
		else
			IMAGE_NEW=YES
		fi
		shift
		;;
	-i | --install)
		shift
		pkgs+=( $1 )
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

rootfs_dnf() {
	_eval sudo dnf --installroot=${ROOTFS_DIR} \
		--releasever=${VERSION_ID} \
		--forcearch=${TARGET_ARCH} \
		--use-host-config -y \
		"$@"
}

rootfs_exec() {
	_eval sudo chroot --userspec=root ${ROOTFS_DIR} "$@"
}

dev_nbd=
dev_uuid=
image_create_and_mount() {
	dev_nbd=/dev/nbd0

	[[ -z ${IMAGE} ]] && return 0

	if [[ ${IMAGE} ]] && [[ ! -e ${IMAGE} ]]; then
		_eval qemu-img create -f ${IMAGE_TYPE} ${IMAGE} 10G
	fi

	_eval sudo modprobe nbd max_part=16 || true
	_eval sudo qemu-nbd --connect ${dev_nbd} ${IMAGE} -f ${IMAGE_TYPE}

	# Make fs if new create
	[[ ${IMAGE_NEW} ]] && _eval sudo mkfs.xfs ${dev_nbd}

	if [[ ${dry_run} ]]; then
		dev_uuid=$(uuid)
	else
		dev_uuid=$(sudo lsblk -o uuid ${dev_nbd} | grep -v UUID)
	fi
	_eval sudo mount ${dev_nbd} ${ROOTFS_DIR}
}

image_unmount() {
	[[ -z ${IMAGE} ]] && return 0

	_eval sudo umount ${ROOTFS_DIR}
	_eval sudo qemu-nbd --disconnect ${dev_nbd}
	_eval sudo rmmod nbd || true
}

print_hint() {
	echo >&2 -e "\033[32m"
	echo >&2 "${ID} ${VERSION_ID} rootfs for ${TARGET_ARCH} has been created at ${ROOTFS_DIR}"
	[[ ${IMAGE} ]] && echo >&2 "UUID=${dev_uuid}"
	echo >&2 -e "\033[0m"
}

cleanup() {
	image_unmount
	print_hint
}
trap cleanup EXIT

_eval sudo mkdir -p ${ROOTFS_DIR}

if [[ ${IMAGE} ]]; then
	image_create_and_mount
fi

rootfs_dnf group install development-tools
rootfs_dnf install ${pkgs[@]}

# Create user and change password
rootfs_exec useradd -G wheel rongtao || true
# NOTE: don't use 'usermod --password "$(openssl passwd -1 123456)" rongtao'
echo "root:123456" | rootfs_exec chpasswd
echo "rongtao:123456" | rootfs_exec chpasswd

# Don't use hostnamectl:
# System has not been booted with systemd as init system (PID 1). Can't operate.
# Failed to connect to system scope bus via local transport: Host is down
rootfs_exec hostname VM-${ID}
