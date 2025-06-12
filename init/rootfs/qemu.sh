#!/bin/bash
# Wrote by Rong Tao
set -e
readonly WHERE_AM_I=$(dirname $(realpath $0))

. ${WHERE_AM_I}/../../qemu/libqemu.sh

readonly prog=qemu-rootfs.sh
readonly qemu=$(get_qemu_kvm_emulator)

vm_name=$(mktemp -u vm-XXXXXX)
kernel=
initrd=
rootfs=
init=

is_initrd=
is_nvdimm=
dry_run=
verbose=
debug=
stdio=

readonly CXL_VOLATILE_MEM=cxl-vmem
readonly CXL_VOLATILE_MEM_LSA=cxl-vmem-lsa
readonly CXL_PMEM=cxl-pmem
readonly CXL_PMEM_4WAY=cxl-pmem-4way
readonly CXL_PMEM_4WAY_SWITCH=cxl-pmem-4way-switch
readonly CXL_TYPES=( ${CXL_VOLATILE_MEM} ${CXL_VOLATILE_MEM_LSA}
			${CXL_PMEM} ${CXL_PMEM_4WAY} ${CXL_PMEM_4WAY_SWITCH})
cxl_type=

declare -a qargs kcmd

__usage__() {
	echo -e "
NAME
	${prog} - test rootfs/initrd with qemu

SYNOPSIS
	${prog} -k=<kernel> -i=<initrd> [-r=<rootfs>] [--stdio]

DESCRIPTION
	-k, --kernel [KERNEL]   specify vmlinuz, bzImage
	    --karg [ARG]        add kernel argument, (may be listed multiple times)
	                        example: --karg=rdinit=/usr/bin/bash

	-i, --initrd [INITRD]   specify initrd image
	-r, --rootfs [ROOTFS]   specify rootfs image. optional
	    --nvdimm            the rootfs used as nvdimm

	--init [/path/to/init]  specify initrd.

	--stdio                 input/output from/to stdio

	--cxl [TYPE]            test CXL, support: ${CXL_TYPES[@]}
	                        debug with debug mode.

	-u, --dry-run           only show commands

	-D, --debug             enable debug mode.
	-v, --verbose           enable verbose mode.
	-h, --help              show this help information

EXAMPLES
	$ sudo ./qemu.sh --kernel /boot/vmlinuz-$(uname -r) \\
		--initrd /boot/initramfs-$(uname -r).img \\
		[--init=/usr/bin/bash]

SEE ALSO
	qemu(1), qemu-kvm(1), etc.
"
	exit ${1-0}
}


TEMP_ARGS=$(getopt --options k:i:r:huDv \
	--long kernel: \
	--long karg: \
	--long initrd: \
	--long rootfs: \
	--long init: \
	--long initrd \
	--long nvdimm \
	--long stdio \
	--long cxl: \
	--long dry-run \
	--long debug \
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
		kcmd+=( $1 )
		shift
		;;
	-i | --initrd)
		shift
		initrd=$1
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
	-D | --debug)
		shift
		debug=YES
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ -z ${kernel} ]] && [[ -z ${initrd} ]]; then
	__usage__
	echo >&2 "ERROR: must specify kernel and initrd"
	exit 1
fi

kernel=$(realpath ${kernel})
initrd=$(realpath ${initrd})

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

cleanup_files+=( $PWD/qmp-${vm_name}.sock ${vm_name}.pid )
cleanup() {
	_eval sudo rm -rf ${cleanup_files[@]}
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

kcmd+=( earlyprintk=serial )
kcmd+=( net.ifnames=0 )
kcmd+=(	selinux=0
	audit=0
	console=tty0
	nokaslr
	)

qargs+=( -kernel ${kernel} )
qargs+=( -initrd ${initrd} )
kcmd+=( rd.break ) # dracut.cmdline(7)

if [[ ${rootfs} ]]; then
	rootfs=$(realpath ${rootfs})

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
		kcmd+=( root=/dev/pmem0 )
	else
		qargs+=( -drive file=${rootfs},format=raw,if=virtio )
		kcmd+=( root=UUID=29efa7e5-23bc-4192-81ca-31d4f342555a )
	fi
fi

if [[ ${stdio} ]]; then
	qargs+=( -serial mon:stdio -nographic )
	kcmd+=( rw console=ttyS0 )
fi

if [[ ${init} ]]; then
	kcmd+=( rdinit=${init} init=${init} )
fi

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_pmem() {
	_eval qemu-img create -f raw cxltest.raw 256M
	_eval qemu-img create -f raw lsa.raw 256M
	cleanup_files+=( cxltest.raw lsa.raw )
	qargs+=(
		-machine q35,cxl=on
		-object memory-backend-file,id=cxl-mem1,share=on,mem-path=$PWD/cxltest.raw,size=256M
		-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=$PWD/lsa.raw,size=256M
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,persistent-memdev=cxl-mem1,lsa=cxl-lsa1,id=cxl-pmem0,sn=0x1
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}

# https://www.qemu.org/docs/master/system/devices/cxl.html
# A setup suitable for 4 way interleave. Only one fixed window provided, to
# enable 2 way interleave across 2 CXL host bridges. Each host bridge has 2
# CXL Root Ports, with the CXL Type3 device directly attached (no switches).
cxl_pmem_4way() {
	local imgs=(cxltest.raw cxltest2.raw cxltest3.raw cxltest4.raw
		lsa.raw lsa2.raw lsa3.raw lsa4.raw)
	for img in ${imgs[@]}
	do
		_eval qemu-img create -f raw ${img} 256M
	done
	cleanup_files+=( ${imgs[@]} )
	qargs+=(
		-machine q35,cxl=on
		-object memory-backend-file,id=cxl-mem1,share=on,mem-path=$PWD/cxltest.raw,size=256M
		-object memory-backend-file,id=cxl-mem2,share=on,mem-path=$PWD/cxltest2.raw,size=256M
		-object memory-backend-file,id=cxl-mem3,share=on,mem-path=$PWD/cxltest3.raw,size=256M
		-object memory-backend-file,id=cxl-mem4,share=on,mem-path=$PWD/cxltest4.raw,size=256M
		-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=$PWD/lsa.raw,size=256M
		-object memory-backend-file,id=cxl-lsa2,share=on,mem-path=$PWD/lsa2.raw,size=256M
		-object memory-backend-file,id=cxl-lsa3,share=on,mem-path=$PWD/lsa3.raw,size=256M
		-object memory-backend-file,id=cxl-lsa4,share=on,mem-path=$PWD/lsa4.raw,size=256M
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device pxb-cxl,bus_nr=222,bus=pcie.0,id=cxl.2
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,persistent-memdev=cxl-mem1,lsa=cxl-lsa1,id=cxl-pmem0,sn=0x1
		-device cxl-rp,port=1,bus=cxl.1,id=root_port14,chassis=0,slot=3
		-device cxl-type3,bus=root_port14,persistent-memdev=cxl-mem2,lsa=cxl-lsa2,id=cxl-pmem1,sn=0x2
		-device cxl-rp,port=0,bus=cxl.2,id=root_port15,chassis=0,slot=5
		-device cxl-type3,bus=root_port15,persistent-memdev=cxl-mem3,lsa=cxl-lsa3,id=cxl-pmem2,sn=0x3
		-device cxl-rp,port=1,bus=cxl.2,id=root_port16,chassis=0,slot=6
		-device cxl-type3,bus=root_port16,persistent-memdev=cxl-mem4,lsa=cxl-lsa4,id=cxl-pmem3,sn=0x4
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.targets.1=cxl.2,cxl-fmw.0.size=4G,cxl-fmw.0.interleave-granularity=8k
	)
}

# https://www.qemu.org/docs/master/system/devices/cxl.html
# An example of 4 devices below a switch suitable for 1, 2 or 4 way interleave:
cxl_pmem_4way_switch() {
	local imgs=(cxltest.raw cxltest1.raw cxltest2.raw cxltest3.raw
		lsa0.raw lsa1.raw lsa2.raw lsa3.raw)
	for img in ${imgs[@]}
	do
		_eval qemu-img create -f raw ${img} 256M
	done
	cleanup_files+=( ${imgs[@]} )
	qargs+=(
		-machine q35,cxl=on
		-object memory-backend-file,id=cxl-mem0,share=on,mem-path=$PWD/cxltest.raw,size=256M
		-object memory-backend-file,id=cxl-mem1,share=on,mem-path=$PWD/cxltest1.raw,size=256M
		-object memory-backend-file,id=cxl-mem2,share=on,mem-path=$PWD/cxltest2.raw,size=256M
		-object memory-backend-file,id=cxl-mem3,share=on,mem-path=$PWD/cxltest3.raw,size=256M
		-object memory-backend-file,id=cxl-lsa0,share=on,mem-path=$PWD/lsa0.raw,size=256M
		-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=$PWD/lsa1.raw,size=256M
		-object memory-backend-file,id=cxl-lsa2,share=on,mem-path=$PWD/lsa2.raw,size=256M
		-object memory-backend-file,id=cxl-lsa3,share=on,mem-path=$PWD/lsa3.raw,size=256M
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port0,chassis=0,slot=0
		-device cxl-rp,port=1,bus=cxl.1,id=root_port1,chassis=0,slot=1
		-device cxl-upstream,bus=root_port0,id=us0
		-device cxl-downstream,port=0,bus=us0,id=swport0,chassis=0,slot=4
		-device cxl-type3,bus=swport0,persistent-memdev=cxl-mem0,lsa=cxl-lsa0,id=cxl-pmem0,sn=0x1
		-device cxl-downstream,port=1,bus=us0,id=swport1,chassis=0,slot=5
		-device cxl-type3,bus=swport1,persistent-memdev=cxl-mem1,lsa=cxl-lsa1,id=cxl-pmem1,sn=0x2
		-device cxl-downstream,port=2,bus=us0,id=swport2,chassis=0,slot=6
		-device cxl-type3,bus=swport2,persistent-memdev=cxl-mem2,lsa=cxl-lsa2,id=cxl-pmem2,sn=0x3
		-device cxl-downstream,port=3,bus=us0,id=swport3,chassis=0,slot=7
		-device cxl-type3,bus=swport3,persistent-memdev=cxl-mem3,lsa=cxl-lsa3,id=cxl-pmem3,sn=0x4
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G,cxl-fmw.0.interleave-granularity=4k
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

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_volatile_mem_lsa() {
	_eval qemu-img create -f raw lsa.raw 256M
	cleanup_files+=( lsa.raw )
	qargs+=(
		-machine q35,cxl=on
		-object memory-backend-ram,id=vmem0,share=on,size=256M
		-object memory-backend-file,id=cxl-lsa0,share=on,mem-path=$PWD/lsa.raw,size=256M
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,volatile-memdev=vmem0,lsa=cxl-lsa0,id=cxl-vmem0
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}

cxl_debug() {
	kcmd+=( "cxl_acpi.dyndbg=+fplm"
		"cxl_pci.dyndbg=+fplm"
		"cxl_core.dyndbg=+fplm"
		"cxl_mem.dyndbg=+fplm"
		"cxl_pmem.dyndbg=+fplm"
		"cxl_port.dyndbg=+fplm"
		"cxl_region.dyndbg=+fplm"
		"cxl_test.dyndbg=+fplm"
		"cxl_mock.dyndbg=+fplm"
		"cxl_mock_mem.dyndbg=+fplm"
		)
}

if [[ ${cxl_type} ]] && [[ ${debug} ]]; then
	cxl_debug
fi

case ${cxl_type} in
${CXL_PMEM})
	cxl_pmem
	;;
${CXL_PMEM_4WAY})
	cxl_pmem_4way
	;;
${CXL_PMEM_4WAY_SWITCH})
	cxl_pmem_4way_switch
	;;
${CXL_VOLATILE_MEM})
	cxl_volatile_mem
	;;
${CXL_VOLATILE_MEM_LSA})
	cxl_volatile_mem_lsa
	;;
esac

_eval ${qemu} ${qargs[@]} -append \"${kcmd[@]}\"
