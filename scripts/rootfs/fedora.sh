#!/bin/bash
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Build fedora/rhel like operate system's rootfs with dnf/rpm package manager.
#
set -e

readonly prog=rootfs-fedora
readonly ROOTFS_FEDORA_DIR=$(dirname $(realpath $0))
readonly TUNA="https://mirrors.tuna.tsinghua.edu.cn"

. ${ROOTFS_FEDORA_DIR}/../liblog.sh
. /etc/os-release

declare TARGET_ARCH=$(uname -m)
declare ROOTFS_DIR

declare IMAGE
declare IMAGE_TYPE
declare IMAGE_NEW

declare INITRD

declare KVER

declare -a pkgs=( autoconf automake binutils cmake dnf dracut gcc gcc-c++ gdb
		git glibc-devel hostname iproute libtool ltrace make
		NetworkManager openssh-server pciutils pkgconf rpm strace
		sudo vim )

declare -a dnf_args

declare force_fedora
declare verbose
declare dry_run

__usage__() {
	echo -e "
${BOLD}NAME${RST}
	${prog} - make rootfs for fedora liked distrobution

${BOLD}SYNOPSIS${RST}
	${prog} --rootfs=<DIR> [--image=<vm.raw|vm.qcow2>]

${BOLD}DESCRIPTION${RST}
	-r, --rootfs [DIR]      specify rootfs directory.
	    --image [NAME]      specify image filename, format: raw, qcow2
	    --initrd [NAME]     generate initrd based on rootfs.

	    --kver [VERSION]    speicfy kernel version, use to install, dracut, etc.

	--force-fedora          force to build fedora if not running on fedora.

	-i, --install [PKG]     install package (may be listed multiple times)

	-u, --dry-run           only show commands
	-v, --verbose           enable verbose mode.
	-h, --help              show this help information

${BOLD}EXAMPLES${RST}
	$ sudo ${prog} --rootfs tmp-rootfs.dir --image rootfs.qcow2 \\
		--initrd initramfs.img --install kernel-modules

${BOLD}AUTHOR${RST}
	Written by Rong Tao.

${BOLD}SEE ALSO${RST}
	dnf(8), dracut(8)
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options r:i:uhv \
	--long rootfs: \
	--long image: \
	--long initrd: \
	--long kver: \
	--long install: \
	--long force-fedora \
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
			error "${IMAGE} is not raw or qcow2."
		fi
		if [[ -e ${IMAGE} ]]; then
			warning "${IMAGE} is already exist."
		else
			IMAGE_NEW=YES
		fi
		shift
		;;
	--initrd)
		shift
		INITRD=$1
		shift
		;;
	--kver)
		shift
		KVER=$1
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
	--force-fedora)
		shift
		force_fedora=YES
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
	error "Must speicfy rootfs directory, see -h, --help"
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
	local SUPPORT_UHC=$(dnf --help | grep -o use-host-config || true)

	_eval sudo dnf --installroot=${ROOTFS_DIR} \
		--releasever=${VERSION_ID} \
		--forcearch=${TARGET_ARCH} \
		${dnf_args[@]} \
		${SUPPORT_UHC:+--use-host-config} \
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
		_eval qemu-img create -f ${IMAGE_TYPE} ${IMAGE} 100G
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

_eval sudo mkdir -p ${ROOTFS_DIR}/etc/yum.repos.d/

# If not running on fedora or rhel like distrobution, just make newest fedora as
# default, and install newest fedora-release rpm first.
if ! [[ " fedora " =~ " ${ID} " ]] && [[ ${force_fedora} ]]; then
	# Default to fedora
	ID=fedora
	VERSION_ID=44 # Newest fedora now(2026-04-08)

	repo_name=tmp
	repo_file=${ROOTFS_DIR}/etc/yum.repos.d/${repo_name}.repo

	pkgs+=( glibc-static )

	_eval "sudo tee ${repo_file} <<-EOF
	[${repo_name}]
	name=Temp Fedora ${VERSION_ID} YUM
	enabled=0
	baseurl=${TUNA}/fedora/releases/${VERSION_ID}/Everything/${TARGET_ARCH}/os/
	gpgcheck=0
	EOF"

	# These is no gpg key in your system, just skip the check.
	dnf_args+=( --nogpgcheck )
	dnf_args+=( --disablerepo=updates )

	rootfs_dnf install -y --disablerepo=* --enablerepo=${repo_name} fedora-release

	_eval sudo rm -f ${repo_file}

# Running on cclinux
elif [[ " cclinux " =~ " ${ID} " ]]; then
	repo_file=${ROOTFS_DIR}/etc/yum.repos.d/tmp.repo

	dnf_args+=( --nogpgcheck )

	_eval sudo cp /etc/yum.repos.d/cclinux.repo ${repo_file}

	rootfs_dnf install -y --disablerepo=* --enablerepo=baseos,appstream,crb system-release

	_eval sudo rm -f ${repo_file}
fi

rootfs_dnf clean all
rootfs_dnf makecache
rootfs_dnf install -y ${pkgs[@]}

# Create user and change password
rootfs_exec useradd -G wheel rongtao || true
# NOTE: don't use 'usermod --password "$(openssl passwd -1 123456)" rongtao'
echo "root:123456" | rootfs_exec chpasswd
echo "rongtao:123456" | rootfs_exec chpasswd

# Don't use hostnamectl:
# System has not been booted with systemd as init system (PID 1). Can't operate.
# Failed to connect to system scope bus via local transport: Host is down
rootfs_exec hostname VM-${ID}

rootfs_exec systemctl enable sshd.service

# In the end, generate initrd if need.
if [[ ${INITRD} ]]; then
	_eval sudo dracut --sysroot=${ROOTFS_DIR} \
		--no-hostonly --force \
		${KVER:+--kver ${KVER}} \
		${INITRD}
fi
