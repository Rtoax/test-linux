#!/bin/bash
# Wrote by Rong Tao
set -e
readonly WHERE_AM_I=$(dirname $(realpath $0))

. ${WHERE_AM_I}/../../qemu/libqemu.sh

readonly prog=qemu-rootfs.sh
readonly qemu=$(get_qemu_kvm_emulator)

vm_name=$(mktemp -u vm-XXXXXX)
memory=2G
f_kernel=
f_initrd=
f_rootfs=
init=
f_nvdimm=

dry_run=
verbose=
debug=
stdio=

readonly CXL_VOLATILE_MEM=cxl-vmem
readonly CXL_VOLATILE_MEM_LSA=cxl-vmem-lsa
readonly CXL_VOLATILE_MEM_4WAY=cxl-vmem-4way
readonly CXL_VOLATILE_MEM_4WAY_SWITCH=cxl-vmem-4way-switch
readonly CXL_PMEM=cxl-pmem
readonly CXL_PMEM_4WAY=cxl-pmem-4way
readonly CXL_PMEM_4WAY_SWITCH=cxl-pmem-4way-switch
readonly CXL_TYPES=( ${CXL_VOLATILE_MEM} ${CXL_VOLATILE_MEM_LSA}
			${CXL_VOLATILE_MEM_4WAY} ${CXL_VOLATILE_MEM_4WAY_SWITCH}
			${CXL_PMEM} ${CXL_PMEM_4WAY} ${CXL_PMEM_4WAY_SWITCH})
cxl_type=
cxl_size=1024M

# q35 for pcie.0
declare -a qmachine+=( q35 accel=kvm )
declare -a qargs kcmds

__usage__() {
	echo -e "
NAME
	${prog} - Running a virtual machine with Qemu

SYNOPSIS
	${prog} -k=<kernel> -i=<initrd> [-r=<rootfs>] [-m=4G] [--stdio]

DESCRIPTION
	-n, --name [NAME]       specify vm name, default: vm- prefix

	-m, --memory [SIZE]     Sets guest startup RAM size, default: ${memory}.

	-k, --kernel [KERNEL]   specify vmlinuz, bzImage
	    --karg [ARG]        add kernel argument, (may be listed multiple times)
	                        example: --karg=rdinit=/usr/bin/bash

	-i, --initrd [INITRD]   specify initrd image
	    --init [PATH]       specify initrd.
	-r, --rootfs [ROOTFS]   optional specify rootfs image. attr: rw

	--nvdimm [FILE]         add a nvdimm pmem

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
		[--rootfs vm.raw] \\
		[--init=/usr/bin/bash]

SEE ALSO
	qemu(1), qemu-kvm(1), etc.
"
	exit ${1-0}
}

check_file_exist_and_exit() {
	local f=$1
	if [[ ! -e ${f} ]]; then
		echo >&2 "ERROR: ${f} is not exist."
		exit 1
	fi
}

TEMP_ARGS=$(getopt --options n:m:k:i:r:huDv \
	--long name: \
	--long memory: \
	--long kernel: \
	--long karg: \
	--long initrd: \
	--long rootfs: \
	--long init: \
	--long nvdimm: \
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
	-n | --name)
		shift
		vm_name=$1
		shift
		;;
	-m | --memory)
		shift
		memory=$1
		shift
		;;
	-k | --kernel)
		shift
		f_kernel=$1
		check_file_exist_and_exit ${f_kernel}
		f_kernel=$(realpath ${f_kernel})
		shift
		;;
	--karg)
		shift
		kcmds+=( $1 )
		shift
		;;
	-i | --initrd)
		shift
		f_initrd=$1
		check_file_exist_and_exit ${f_initrd}
		f_initrd=$(realpath ${f_initrd})
		shift
		;;
	-r | --rootfs)
		shift
		f_rootfs=$1
		if ! [[ " raw qcow2 " =~ " ${f_rootfs##*.} " ]]; then
			echo >&2 "ERROR: ${f_rootfs} is not raw or qcow2."
			exit 1
		fi
		check_file_exist_and_exit ${f_rootfs}
		f_rootfs=$(realpath ${f_rootfs})
		shift
		;;
	--init)
		shift
		init=$1
		shift
		;;
	--nvdimm)
		shift
		f_nvdimm=$1
		check_file_exist_and_exit ${f_nvdimm}
		f_nvdimm=$(realpath ${f_nvdimm})
		shift
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

if [[ -z ${f_kernel} ]] && [[ -z ${f_initrd} ]]; then
	__usage__
	echo >&2 "ERROR: must specify kernel and initrd"
	exit 1
fi

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

image2uuid() {
	if [[ ${dry_run} ]]; then
		uuid
	else
		local img=$1
		local img_type=${img##*.}
		if ! [[ " raw qcow2 " =~ " ${img_type} " ]]; then
			echo >&2 "ERROR: ${img} is not raw or qcow2."
			exit 1
		fi

		# only raw could use this, qcow2 don't
		case ${img_type} in
		raw)
			local dev_loop=$(sudo losetup --find --show ${img})
			sudo lsblk -o uuid ${dev_loop} | grep -v UUID
			sudo losetup --detach ${dev_loop}
			;;
		qcow2)
			local dev_nbd=/dev/nbd0
			sudo modprobe nbd max_part=16 || true >/dev/null
			sudo qemu-nbd --connect ${dev_nbd} ${img} -f ${img_type} >/dev/null && sleep 1
			sudo lsblk -o uuid ${dev_nbd} | grep -v UUID
			sudo qemu-nbd --disconnect ${dev_nbd} >/dev/null
			sudo rmmod nbd || true >/dev/null
			;;
		esac
	fi
}

cleanup_files+=( $PWD/qmp-${vm_name}.sock ${vm_name}.pid )
cleanup() {
	_eval sudo rm -rf ${cleanup_files[@]}
}
trap cleanup EXIT

config_basic() {
	qargs+=( -name ${vm_name} )
	qargs+=( -uuid $(uuid) )
	qargs+=( -enable-kvm )
	qargs+=( -qmp unix:$PWD/qmp-${vm_name}.sock,server=on,wait=off )
	qargs+=( -pidfile ${vm_name}.pid)

	if [[ ${stdio} ]]; then
		qargs+=( -serial mon:stdio -nographic )
	fi
}

config_memory() {
	local m=( ${memory} )
	m+=( slots=0 )
	m+=( maxmem=32768M )
	qargs+=( -m $(IFS=,; echo "${m[*]}") )
}

config_cpu() {
	qargs+=( -cpu host,migratable=off -smp cpus=4 )
}

config_uefi() {
	qargs+=( -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/OVMF_CODE.fd
		-drive if=pflash,format=raw,file=/usr/share/OVMF/OVMF_VARS.fd )
}

config_pci() {
	qargs+=(-device pcie-root-port,id=pcie.1,bus=pcie.0,port=1,chassis=1,slot=0
		-device pcie-root-port,id=pcie.2,bus=pcie.0,port=2,chassis=2,slot=0)
}

add_net_nic_user() {
	qargs+=(-netdev type=user,id=net0
		-device virtio-net-pci,bus=pcie.0,netdev=net0,addr=6.0 )
}

# Create tap0 with:
# $ sudo ip tuntap add tap0 mode tap
# $ sudo ip addr add 192.168.100.1/24 dev tap0
# $ sudo sysctl net.ipv4.ip_forward=1
# $ sudo iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE
add_net_nic_tap() {
	qargs+=( -net nic -net tap,ifname=tap0,script=no,downscript=no )
}

# Usage:
# on hostos:
# $ ssh -p8080 root@localhost
add_net_nic_user_tap() {
	qargs+=( -net user,hostfwd=tcp::8080-:22
		-net nic,model=virtio
		-device virtio-net,netdev=network0
		-netdev tap,id=network0,ifname=tap0,script=no,downscript=no )
}

config_net() {
	add_net_nic_user_tap
}

config_kernel() {
	qargs+=( -kernel ${f_kernel} )
	qargs+=( -initrd ${f_initrd} )

	kcmds+=( earlyprintk=serial )
	kcmds+=( net.ifnames=0 )
	kcmds+=( selinux=0 audit=0 nokaslr rw )
	kcmds+=( console=tty0 console=ttyS0 )

	if [[ ${init} ]]; then
		kcmds+=( rdinit=${init} init=${init} )
	fi
}

config_rootfs() {
	if [[ -z ${f_rootfs} ]]; then
		# if not rootfs, we should break in initrd.
		kcmds+=( rd.break ) # dracut.cmdline(7)
		return 0
	fi

	local rootfs_type=${f_rootfs##*.}

	rootfs_virtio() {
		local virtio_id=$(mktemp -u virtio-XXXXXX)
		qargs+=( -drive file=${f_rootfs},format=${rootfs_type},if=none,id=${virtio_id}
			-device virtio-blk,drive=${virtio_id} )
	}
	rootfs_sata() {
		local sata_id=$(mktemp -u sata-XXXXXX)
		qargs+=( -device ahci,id=ahci0
			-drive if=none,file=${f_rootfs},format=${rootfs_type},id=${sata_id}
			-device ide-hd,bus=ahci0.0,drive=${sata_id} )
	}
	rootfs_nvme() {
		local drive_id=$(mktemp -u nvme-XXXXXX)
		qargs+=( -drive if=none,file=${f_rootfs},format=${rootfs_type},id=${drive_id}
			-device nvme,drive=${drive_id},serial=sn-${drive_id} )
	}
	rootfs_scsi() {
		qargs+=( -device virtio-scsi-pci,id=scsi0
			-device scsi-hd,drive=hd0
			-drive file=${f_rootfs},if=none,aio=native,cache=none,format=${rootfs_type},id=hd0 )
	}
	rootfs_virtio

	kcmds+=( root=UUID=$(image2uuid ${f_rootfs}) )
}

config_nvdimm() {
	local size nvdimm_id

	if [[ -z ${f_nvdimm} ]]; then
		return 0
	fi

	size=$(stat --format=%s ${f_nvdimm})
	skip_resize() {
		if [[ ${size} -lt $((1024*1024*1024)) ]]; then
			size=$((1024*1024*1024))
		fi
	}
	qmachine+=( nvdimm=on )
	nvdimm_id=$(mktemp -u nvdimm-XXXXXX)
	qargs+=( -device nvdimm,id=nv0,memdev=${nvdimm_id},unarmed=on )
	qargs+=( -object memory-backend-file,id=${nvdimm_id},mem-path=${f_nvdimm},size=${size},readonly=on )
}

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_pmem() {
	_eval qemu-img create -f raw cxltest.raw ${cxl_size}
	_eval qemu-img create -f raw lsa.raw ${cxl_size}
	cleanup_files+=( cxltest.raw lsa.raw )
	qargs+=(
		-object memory-backend-file,id=cxl-mem1,share=on,mem-path=$PWD/cxltest.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=$PWD/lsa.raw,size=${cxl_size}
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
		_eval qemu-img create -f raw ${img} ${cxl_size}
	done
	cleanup_files+=( ${imgs[@]} )
	qargs+=(
		-object memory-backend-file,id=cxl-mem1,share=on,mem-path=$PWD/cxltest.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-mem2,share=on,mem-path=$PWD/cxltest2.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-mem3,share=on,mem-path=$PWD/cxltest3.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-mem4,share=on,mem-path=$PWD/cxltest4.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-lsa1,share=on,mem-path=$PWD/lsa.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-lsa2,share=on,mem-path=$PWD/lsa2.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-lsa3,share=on,mem-path=$PWD/lsa3.raw,size=${cxl_size}
		-object memory-backend-file,id=cxl-lsa4,share=on,mem-path=$PWD/lsa4.raw,size=${cxl_size}
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
	for i in $(seq 0 1 3)
	do
		_eval qemu-img create -f raw cxltest${i}.raw ${cxl_size}
		_eval qemu-img create -f raw lsa${i}.raw ${cxl_size}
		cleanup_files+=( cxltest${i}.raw lsa${i}.raw )

		qargs+=( -object memory-backend-file,id=cxl-mem${i},share=on,mem-path=$PWD/cxltest${i}.raw,size=${cxl_size}
			-object memory-backend-file,id=cxl-lsa${i},share=on,mem-path=$PWD/lsa${i}.raw,size=${cxl_size}
			)
	done
	qargs+=(
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port0,chassis=0,slot=0
		-device cxl-rp,port=1,bus=cxl.1,id=root_port1,chassis=0,slot=1
		-device cxl-upstream,bus=root_port0,id=us0
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G,cxl-fmw.0.interleave-granularity=4k
	)
	for i in $(seq 0 1 3)
	do
		qargs+=( -device cxl-downstream,port=${i},bus=us0,id=swport${i},chassis=0,slot=$((${i}+2))
			-device cxl-type3,bus=swport${i},persistent-memdev=cxl-mem${i},lsa=cxl-lsa${i},id=cxl-pmem${i},sn=0x1
			)
	done
}

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_volatile_mem() {
	qargs+=(
		-object memory-backend-ram,id=vmem0,share=on,size=${cxl_size}
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,volatile-memdev=vmem0,id=cxl-vmem0
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}

# https://www.qemu.org/docs/master/system/devices/cxl.html
cxl_volatile_mem_lsa() {
	_eval qemu-img create -f raw lsa.raw ${cxl_size}
	cleanup_files+=( lsa.raw )
	qargs+=(
		-object memory-backend-ram,id=vmem0,share=on,size=${cxl_size}
		-object memory-backend-file,id=cxl-lsa0,share=on,mem-path=$PWD/lsa.raw,size=${cxl_size}
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-type3,bus=root_port13,volatile-memdev=vmem0,lsa=cxl-lsa0,id=cxl-vmem0
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}

cxl_volatile_mem_4way() {
	qargs+=(
		-object memory-backend-ram,id=vmem0,share=on,size=${cxl_size}
		-object memory-backend-ram,id=vmem1,share=on,size=${cxl_size}
		-object memory-backend-ram,id=vmem2,share=on,size=${cxl_size}
		-object memory-backend-ram,id=vmem3,share=on,size=${cxl_size}
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port13,chassis=0,slot=2
		-device cxl-rp,port=1,bus=cxl.1,id=root_port14,chassis=0,slot=3
		-device cxl-rp,port=2,bus=cxl.1,id=root_port15,chassis=0,slot=4
		-device cxl-rp,port=3,bus=cxl.1,id=root_port16,chassis=0,slot=5
		-device cxl-type3,bus=root_port13,volatile-memdev=vmem0,id=cxl-vmem0
		-device cxl-type3,bus=root_port14,volatile-memdev=vmem1,id=cxl-vmem1
		-device cxl-type3,bus=root_port15,volatile-memdev=vmem2,id=cxl-vmem2
		-device cxl-type3,bus=root_port16,volatile-memdev=vmem3,id=cxl-vmem3
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G
	)
}

cxl_volatile_mem_4way_switch() {
	for i in $(seq 0 1 3)
	do
		qargs+=( -object memory-backend-ram,id=vmem${i},share=on,size=${cxl_size}
			)
	done
	qargs+=(
		-device pxb-cxl,bus_nr=12,bus=pcie.0,id=cxl.1
		-device cxl-rp,port=0,bus=cxl.1,id=root_port0,chassis=0,slot=0
		-device cxl-rp,port=1,bus=cxl.1,id=root_port1,chassis=0,slot=1
		-device cxl-upstream,bus=root_port0,id=us0
		-M cxl-fmw.0.targets.0=cxl.1,cxl-fmw.0.size=4G,cxl-fmw.0.interleave-granularity=4k
	)
	for i in $(seq 0 1 3)
	do
		qargs+=(
			-device cxl-downstream,port=${i},bus=us0,id=swport${i},chassis=0,slot=$((${i}+2))
			-device cxl-type3,bus=swport${i},volatile-memdev=vmem${i},id=cxl-vmem${i},sn=0x1
			)
	done
}

cxl_debug() {
	kcmds+=( "cxl_acpi.dyndbg=+fplm"
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

config_cxl() {
	if [[ ${cxl_type} ]] && [[ ${debug} ]]; then
		cxl_debug
	fi

	if [[ ${cxl_type} ]]; then
		qmachine+=( cxl=on )
		# Disable ACPI CXL enumeration at boot
		# kcmds+=( acpi=off )
		kcmds+=( cxl.mem=disable cxl.acpi=0 )
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
	${CXL_VOLATILE_MEM_4WAY})
		cxl_volatile_mem_4way
		;;
	${CXL_VOLATILE_MEM_4WAY_SWITCH})
		cxl_volatile_mem_4way_switch
		;;
	esac
}

config_basic
config_memory
config_cpu
config_uefi
config_pci
config_net
config_kernel
config_rootfs
config_nvdimm
config_cxl

qargs+=( -machine $(IFS=,; echo "${qmachine[*]}") )

_eval ${qemu} ${qargs[@]} -append \"${kcmds[@]}\"
