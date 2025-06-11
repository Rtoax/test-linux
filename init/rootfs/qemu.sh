#!/bin/bash
# Wrote by Rong Tao
set -e
readonly WHERE_AM_I=$(dirname $(realpath $0))

. ${WHERE_AM_I}/../../qemu/libqemu.sh

readonly prog=qemu-rootfs.sh
readonly qemu=$(get_qemu_kvm_emulator)

vm_name=$(mktemp -u vm-XXXXXX)
kernel=
rootfs=
init=

is_initrd=
is_nvdimm=
dry_run=
verbose=
stdio=

readonly CXL_VOLATILE_MEM=cxl-vmem
readonly CXL_PMEM=cxl-pmem
readonly CXL_TYPES=( ${CXL_VOLATILE_MEM} ${CXL_PMEM} )
cxl_type=

declare -a qargs kargs

__usage__() {
	echo -e "
NAME
	${prog} - test rootfs/initrd with qemu

SYNOPSIS
	${prog} -k=<kernel> -r=<rootfs> [--stdio]

DESCRIPTION
	-k, --kernel [KERNEL]   specify vmlinuz, bzImage
	    --karg [ARG]        add kernel argument, (may be listed multiple times)
	                        example: --karg=rdinit=/usr/bin/bash

	-r, --rootfs [ROOTFS]   specify rootfs image
	    --initrd            the rootfs used as initrd
	    --nvdimm            the rootfs used as nvdimm

	--init [/path/to/init]  specify initrd.

	--stdio                 input/output from/to stdio

	--cxl [TYPE]            test CXL, support type: ${CXL_TYPES[@]}

	-u, --dry-run           only show commands

	-v, --verbose           show verbose information
	-h, --help              show this help information

EXAMPLES
	$ sudo ./qemu.sh -k /boot/vmlinuz-$(uname -r) -r /boot/initramfs-$(uname -r).img --initrd [--init=/usr/bin/bash]

SEE ALSO
	qemu(1), qemu-kvm(1), etc.
"
	exit ${1-0}
}


TEMP_ARGS=$(getopt --options k:r:huv \
	--long kernel: \
	--long karg: \
	--long rootfs: \
	--long init: \
	--long initrd \
	--long nvdimm \
	--long stdio \
	--long cxl: \
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
	--karg)
		shift
		kargs+=( $1 )
		shift
		;;
	-r | --rootfs)
		shift
		rootfs=$1
		shift
		;;
	--init)
		shift
		init=$1
		shift
		;;
	--initrd)
		shift
		is_initrd=YES
		;;
	--nvdimm)
		shift
		is_nvdimm=YES
		;;
	--cxl)
		shift
		cxl_type=$1
		if ! [[ " ${CXL_TYPES[@]} " =~ " ${cxl_type} " ]]; then
			echo >&2 "ERROR: cxl type only support <${CXL_TYPES[@]}>"
			exit 1
		fi
		shift
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

cleanup() {
	sudo rm -rf $PWD/qmp-${vm_name}.sock ${vm_name}.pid
}
trap cleanup EXIT

qargs+=( -name ${vm_name} )
qargs+=( -uuid $(uuid) )
qargs+=( -enable-kvm )
qargs+=( -qmp unix:$PWD/qmp-${vm_name}.sock,server=on,wait=off )
qargs+=( -pidfile ${vm_name}.pid)
qargs+=( -cpu max )
qargs+=( -m 2048M,slots=10,maxmem=129139M )
# TODO: NIC
qargs+=( -net user,host=10.0.2.10,hostfwd=tcp:127.0.0.1:10021-:22 )
qargs+=( -net nic,model=e1000 )

kargs+=( earlyprintk=serial )
kargs+=( net.ifnames=0 )
kargs+=( selinux=0 )

if [[ ${is_initrd} ]]; then
	qargs+=( -initrd ${rootfs} )
	kargs+=( rd.break ) # dracut.cmdline(7)
else
	if [[ ${is_nvdimm} ]]; then
		size=$(stat --format=%s ${rootfs})
		skip_resize() {
			if [[ ${size} -lt $((1024*1024*1024)) ]]; then
				size=$((1024*1024*1024))
			fi
		}
		qargs+=( -machine nvdimm=on )
		qargs+=( -device nvdimm,id=nv0,memdev=mem0,unarmed=on )
		qargs+=( -object memory-backend-file,id=mem0,mem-path=${rootfs},size=${size},readonly=on )
		kargs+=( root=/dev/pmem0 )
	else
		qargs+=( -drive file=${rootfs},format=raw,if=virtio )
		kargs+=( root=/dev/vda )
	fi
fi

if [[ ${stdio} ]]; then
	qargs+=( -serial mon:stdio -nographic )
	kargs+=( rw console=ttyS0 )
fi

if [[ ${init} ]]; then
	kargs+=( rdinit=${init} init=${init} )
fi

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_pmem() {
	qargs+=(
		-machine q35,cxl=on
		-object memory-backend-file,id=cxl-mem1,share=on,mem-path=/home/sda/qcow2s/cxltest.raw,size=256M
		-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=/home/sda/qcow2s/lsa.raw,size=256M
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,persistent-memdev=cxl-mem1,lsa=cxl-lsa1,id=cxl-pmem0,sn=0x1
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_volatile_mem() {
	qargs+=(
		-machine q35,cxl=on
		-object memory-backend-ram,id=vmem0,share=on,size=256M
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,volatile-memdev=vmem0,id=cxl-vmem0
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}
case ${cxl_type} in
${CXL_VOLATILE_MEM})
	cxl_volatile_mem
	;;
${CXL_PMEM})
	cxl_pmem
	;;
esac

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

_eval ${qemu} ${qargs[@]} -kernel ${kernel} -append \"${kargs[@]}\"
