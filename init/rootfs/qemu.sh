#!/bin/bash
set -e

. ../../libs/qemu.sh

readonly prog=qemu-rootfs.sh
readonly qemu=$(get_qemu_kvm_emulator)

kernel=
rootfs=
initrd=
dry_run=
verbose=
stdio=

__usage__() {
	echo -e "
NAME
	${prog} - test rootfs/initrd with qemu

SYNOPSIS
	${prog} -k=<kernel> -r=<rootfs> [--stdio]

DESCRIPTION
	-k, --kernel [KERNEL]   specify vmlinuz
	-r, --rootfs [ROOTFS]   specify rootfs image
	    --initrd            the rootfs used as initrd

	--stdio                 input/output from/to stdio

	-u, --dry-run           only show commands

	-v, --verbose           show verbose information
	-h, --help              show this help information

EXAMPLES
	$ sudo ./qemu.sh -k /boot/vmlinuz-$(uname -r) -r /boot/initramfs-$(uname -r).img --initrd

SEE ALSO
	qemu(1), qemu-kvm(1), etc.
"
	exit ${1-0}
}

declare -a qemu_args kernel_args

TEMP_ARGS=$(getopt --options k:r:huv \
	--long kernel: \
	--long rootfs: \
	--long initrd \
	--long stdio \
	--long dry-run \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-k | --kernel)
		shift
		kernel=$1
		shift
		;;
	-r | --rootfs)
		shift
		rootfs=$1
		shift
		;;
	--initrd)
		shift
		initrd=YES
		;;
	--stdio)
		shift
		stdio=YES
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

[[ -z ${kernel} ]] && __usage__ && exit 1
[[ -z ${rootfs} ]] && __usage__ && exit 1
rootfs=$(realpath ${rootfs})

if [[ ${verbose} ]]; then
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
fi

if [[ ${initrd} ]]; then
	qemu_args+=( -initrd ${rootfs} )
	kernel_args+=( rd.break ) # dracut.cmdline(7)
else
	qemu_args+=( -drive file=${rootfs},format=raw,if=virtio )
	kernel_args+=( root=/dev/vda )
fi

if [[ ${stdio} ]]; then
	qemu_args+=( -serial mon:stdio -nographic )
	kernel_args+=( rw console=ttyS0 )
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

_eval ${qemu} -name vm-test-rootfs -uuid $(uuid) \
	-qmp unix:$PWD/qmp.sock,server=on,wait=off \
	-m 2048M,slots=10,maxmem=129139M \
	${qemu_args[@]} \
	-kernel ${kernel} -append \"${kernel_args[@]}\"
