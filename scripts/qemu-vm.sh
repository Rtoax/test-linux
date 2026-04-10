#!/bin/bash
# Use the qemu command to create a virtual machine directly, without using
# libvirt, but directly use the qemu command line parameters.
#
# Copyright (C) 2025-2026 Rong Tao
#
set -e

readonly QEMU_VM_ROOT=$(dirname $(realpath $0))

. ${QEMU_VM_ROOT}/liblog.sh
. ${QEMU_VM_ROOT}/libqemu.sh
. ${QEMU_VM_ROOT}/libstring.sh

readonly prog=qemu-vm
readonly arch=$(uname -m)
QEMU_KVM=$(get_qemu_kvm_emulator)

readonly bus_pcie0=pcie.0 # q35 default root bus
pcie_root_port_num=2

q_vm_name=$(mktemp -u vm-XXXXXX)
q_memory=2G

f_kernel=
f_initrd=
k_rdinit=

f_rootfs=
f_rootfs_disk_type=
k_init=
k_root=
# root mount attr: ro, rw. default: rw
k_rw=rw

f_nvdimm=

f_virtiofs_sock=
q_virtiofs_tag=

q_stdio=
q_gdb=

dry_run=
verbose=
debug=

# CXL
# ===
# - CXL level: pxb-cxl -> cxl-rp -> cxl-switch/cxl-type3
#   pxb: PCIe eXpander Bridge
#   rp: Root Port
# - CXL fmw: Fixed Memory Window
# - Refs:
#   https://www.qemu.org/docs/master/system/devices/cxl.html
readonly CXL_DEV_VOLATILE_MEM=cxl-vmem
readonly CXL_DEV_VOLATILE_MEM_LSA=cxl-vmem-lsa
readonly CXL_DEV_VOLATILE_MEM_4WAY=cxl-vmem-4way
readonly CXL_DEV_VOLATILE_MEM_4WAY_SWITCH=cxl-vmem-4way-switch
readonly CXL_DEV_PMEM=cxl-pmem
readonly CXL_DEV_PMEM_4WAY=cxl-pmem-4way
readonly CXL_DEV_PMEM_4WAY_SWITCH=cxl-pmem-4way-switch
readonly CXL_DEVICES=( ${CXL_DEV_VOLATILE_MEM} ${CXL_DEV_VOLATILE_MEM_LSA}
			${CXL_DEV_VOLATILE_MEM_4WAY} ${CXL_DEV_VOLATILE_MEM_4WAY_SWITCH}
			${CXL_DEV_PMEM} ${CXL_DEV_PMEM_4WAY} ${CXL_DEV_PMEM_4WAY_SWITCH})
# cxl-pxb id=
declare -a cxl_pxb_ids
declare -a cxl_rp_ids cxl_rp_buss cxl_rp_ports cxl_rp_slots
declare cxl_device
declare cxl_size=1024M

readonly DISK_TYPE_VIRTIO=virtio
readonly DISK_TYPE_SATA=sata
readonly DISK_TYPE_NVME=nvme
readonly DISK_TYPE_NVDIMM=nvdimm
readonly DISK_TYPE_SCSI=scsi
readonly DISK_TYPES=( ${DISK_TYPE_VIRTIO} ${DISK_TYPE_SATA} ${DISK_TYPE_NVME}
			${DISK_TYPE_SCSI} ${DISK_TYPE_NVDIMM} )

declare -a qargs qmachine kcmds
declare -a cleanup_files

__usage__() {
	echo -e "
${BOLD}NAME${RST}
    ${prog} - Running a virtual machine with Qemu-KVM

${BOLD}SYNOPSIS${RST}
    ${prog} -k=<kernel> -i=<initrd> [-r=<rootfs>] [-m=4G] [--stdio]

${BOLD}DESCRIPTION${RST}
    Running a virtual machine with Qemu-KVM, support flexable arguments.

${BOLD}OPTIONS${RST}
    -n, --name [NAME]       specify vm name, default: vm- prefix

    -m, --memory [SIZE]     Sets guest startup RAM size, default: ${q_memory},
                            format see ${UL}SIZE${RST} section.

    -k, --kernel [KERNEL]   specify vmlinuz, bzImage
        --karg [ARG]        add kernel argument, (may be listed multiple times)
                            example: --karg=${GRAY}rdinit=/usr/bin/bash${RST}

    -i, --initrd [INITRD]   specify initrd image
        --rdinit [PATH]     specify initrd's init process.

    -r, --rootfs [type=TYPE,file=ROOTFS,<rw|ro>]|[ROOTFS]
                            optional specify rootfs image.
                            TYPE=\"${DISK_TYPES[@]}\"
        --init [PATH]       specify rootfs's init process.
        --root [ROOT]       specify root= in kernel cmdline, default use UUID
                            of rootfs image.

    --nvdimm [FILE]         add a nvdimm pmem

    --stdio                 input/output from/to stdio. Default ${GRAY}TERM=${RST}${UL}vt220${RST}
                            if stdio, you could set ${UL}TERM=xterm-256color${RST}
                            or ${UL}TERM=linux${RST} in your virtual machine.

  ${BOLD}VirtIO OPTIONS${RST}
    --virtio-fs-sock [SOCK] specify virtio-fs vhost-fs.sock, this sock created
                            by ${GRAY}$ virtiofsd --socket-path=/var/run/vhost-fs.sock -o source=/path/to/host/${RST}
    --virtio-fs-tag [TAG]   specify virtio-fs tag, like: ${GRAY}myfs${RST}

  ${BOLD}QEMU OPTIONS${RST}
    -Q, --qemu [qemu-kvm]   specify qemu emulator binary.
        --gdb               enable qemu debugging, usage:${GRAY}
                            $ gdb -q kernel.elf
                            (gdb) target remote :1234
                            (gdb) hbreak start_kernel
                            (gdb) continue${RST}
                            the ${UL}kernel.elf${RST} also could get:${GRAY}
                            $ objcopy --only-keep-debug vmlinux kernel.elf${RST}

  ${BOLD}CXL OPTIONS${RST}
    --cxl [ARGS]            CXL by Qemu. please see ${BOLD}--cxl help${RST}

                            CXL require Qemu >= ${UL}9.0${RST} on aarch64,
                            Qemu >= ${UL}7.2${RST} on x86_64.

  ${BOLD}COMMON OPTIONS${RST}
    -u, --dry-run           only show commands
    -D, --debug             enable debug mode.
    -v, --verbose           enable verbose mode.
    -h, --help              show this help information

${BOLD}EXAMPLES${RST}
    $ sudo ${prog} --kernel ${GRAY}${ITALIC}/boot/vmlinuz-${arch}${RST} \\
        --initrd ${GRAY}${ITALIC}/boot/initramfs-${arch}.img${RST} ${GRAY}[--rdinit=/bin/bash]${RST} \\
        ${GRAY}[--rootfs vm.raw] [--init=/usr/bin/bash]${RST}

${BOLD}FORMAT${RST}

  ${UL}SIZE${RST}: B, K, KB, KiB, M, MB, MiB, G, GB, GiB

${BOLD}SEE ALSO${RST}
    qemu(1), qemu-kvm(1), etc.
"
	exit ${1-0}
}

check_file_exist_and_exit() {
	local f=$1
	if [[ ! -e ${f} ]]; then
		error "${f} is not exist."
	fi
}

is_qemu_format() {
	local img=$1
	local img_type=${img##*.}
	if [[ " raw qcow2 " =~ " ${img_type} " ]]; then
		echo yes
	else
		echo no
	fi
}

check_qemu_format_and_exit() {
	if [[ $(is_qemu_format ${f_rootfs}) != yes ]]; then
		error "${f_rootfs} is not raw or qcow2."
	fi
}

# Format: type=TYPE,file=FILE,ro,rw
handle_rootfs_arg() {
	local arg args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -gt 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			type)
				f_rootfs_disk_type=${arg:5}
				if ! [[ " ${DISK_TYPES[@]} " =~ " ${f_rootfs_disk_type} " ]]; then
					error "rootfs unsupport ${arg}"
				fi
				;;
			file)
				f_rootfs=${arg:5}
				;;
			rw | ro)
				if [[ ${arg} != ro ]] && [[ ${arg} != rw ]]; then
					error "rootfs unknown ${arg}"
				fi
				k_rw=${arg}
				;;
			*)
				error "rootfs unknown ${arg}"
				;;
			esac
		done
		if [[ -z ${f_rootfs} ]]; then
			error "not found file= for rootfs"
		fi
	else
		f_rootfs=$1
	fi

	if [[ -z ${f_rootfs_disk_type} ]]; then
		f_rootfs_disk_type=${DISK_TYPE_VIRTIO}
	fi

	check_file_exist_and_exit ${f_rootfs}
	check_qemu_format_and_exit ${f_rootfs}

	f_rootfs=$(realpath ${f_rootfs})
}

cxl_arg_help() {
	echo -e "
${BOLD}CXL ARGUMENTS SYNTAX${RST}

${BOLD}--cxl [DEV]${RST}
${BOLD}--cxl device=[DEV]${RST}
${BOLD}--cxl pxb=<name>${RST}: create CXL PXB
${BOLD}--cxl rp=<name>,bus=<name>,port=<n>,slot=<n>${RST}: create CXL RootPort

${BOLD}[DEV]${RST}
${GRAY}${CXL_DEVICES[@]}${RST}
"
	exit 0
}

# Formats: device=<name>
handle_cxl_arg() {
	local arg args
	local device
	local pxb_id
	local bus port slot
	local rp_id

	# Pre handle
	args=( $(echo $1 | tr ',' ' ') )
	for arg in ${args[@]}
	do
		case ${arg%%=*} in
		help)
			cxl_arg_help
			;;
		esac
	done
	unset args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -gt 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			device)
				device=${arg:7}
				;;
			pxb)
				pxb_id=${arg:4}
				;;
			rp)
				rp_id=${arg:3}
				;;
			bus)
				bus=${arg:4}
				;;
			port)
				port=${arg:5}
				;;
			slot)
				slot=${arg:5}
				;;
			*)
				error "cxl unknown arg ${arg}"
				;;
			esac
		done
	else
		device=$1
	fi

	if [[ ${device} ]] && [[ ${pxb_id} ]]; then
		error "--cxl not allow specify pxb= for device"
	fi

	if [[ ${device} ]] && [[ ${rp_id} ]]; then
		error "--cxl not allow specify rp= for device"
	fi

	if [[ ${pxb_id} ]] && [[ ${rp_id} ]]; then
		error "--cxl not allow specify pxb and rp at the save time"
	fi

	if [[ ${rp_id} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${port} ]] || [[ -z ${slot} ]]; then
			error "--cxl rp need bus= port= slot= at the same time"
		fi
	fi

	# set global
	cxl_device=${device}
	cxl_pxb_ids+=( ${pxb_id} )
	cxl_rp_ids+=( ${rp_id} )
	cxl_rp_buss+=( ${bus} )
	cxl_rp_ports+=( ${port} )
	cxl_rp_slots+=( ${slot} )

	# 2 spaces for empty cxl_device.
	if ! [[ "  ${CXL_DEVICES[@]} " =~ " ${cxl_device} " ]]; then
		error "Bad '${cxl_device}', cxl type only support <${CXL_DEVICES[@]}>"
	fi
}

TEMP_ARGS=$(getopt --options n:m:k:i:r:Q:huDv \
	--long name: \
	--long memory: \
	--long kernel: \
	--long karg: \
	--long initrd: \
	--long rdinit: \
	--long rootfs: \
	--long init: \
	--long root: \
	--long nvdimm: \
	--long stdio \
	--long cxl: \
	--long virtio-fs-sock: \
	--long virtio-fs-tag: \
	--long dry-run \
	--long qemu: \
	--long gdb \
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
		q_vm_name=$1
		shift
		;;
	-m | --memory)
		shift
		q_memory=$(sizeceilfmt $1)
		if [[ -z ${q_memory} ]]; then
			error "Bad memory parameter ${q_memory}"
		fi
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
		handle_rootfs_arg ${1}
		shift
		;;
	--rdinit)
		shift
		k_rdinit=$1
		shift
		;;
	--init)
		shift
		k_init=$1
		shift
		;;
	--root)
		shift
		k_root=$1
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
		handle_cxl_arg ${1}
		shift
		;;
	--virtio-fs-sock)
		shift
		f_virtiofs_sock=$1
		check_file_exist_and_exit ${f_virtiofs_sock}
		shift
		;;
	--virtio-fs-tag)
		shift
		q_virtiofs_tag=$1
		shift
		;;
	--stdio)
		shift
		q_stdio=ON
		;;
	-Q | --qemu)
		shift
		QEMU_KVM=$1
		if [[ ! -f ${QEMU_KVM} ]]; then
			error "Not found qemu ${QEMU_KVM}"
		fi
		shift
		;;
	--gdb)
		shift
		q_gdb=ON
		;;
	-h | --help)
		shift
		__usage__
		;;
	-u | --dry-run)
		shift
		dry_run=ON
		;;
	-v | --verbose)
		shift
		verbose=ON
		;;
	-D | --debug)
		shift
		debug=ON
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ -z ${f_kernel} ]] && [[ -z ${f_initrd} ]]; then
	__usage__
	error "must specify kernel and initrd"
fi

if [[ ${verbose} ]]; then
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
fi

_eval()
{
	if [[ -z ${dry_run} ]]; then
		echo >&2 -e "${BOLD}${GREEN}Startup: $@${RST}"
		eval "$@"
		echo >&2 -e "${BOLD}${YELLOW}Done: $@${RST}"
	else
		echo "$@"
	fi
}

image2uuid() {
	if [[ ${dry_run} ]]; then
		uuid
		return
	fi

	local img=$1
	local img_type=${img##*.}

	check_qemu_format_and_exit ${img}

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
}

cleanup() {
	_eval sudo rm -rf ${cleanup_files[@]}
}
trap cleanup EXIT

config_basic() {
	qargs+=( -name ${q_vm_name} )
	qargs+=( -uuid $(uuid) )
	qargs+=( -enable-kvm )

	qargs+=( -qmp unix:$PWD/qmp-${q_vm_name}.sock,server=on,wait=off )
	qargs+=( -pidfile ${q_vm_name}.pid)
	cleanup_files+=( $PWD/qmp-${q_vm_name}.sock ${q_vm_name}.pid )

	if [[ ${q_stdio} ]]; then
		# Default TERM=vt220 if stdio, you could specify
		# TERM=xterm-256color or TERM=linux in your virtual machine.
		qargs+=( -serial mon:stdio -nographic )
	fi

	case ${arch} in
	x86_64)
		qmachine+=( type=q35 )
		;;
	aarch64)
		qmachine+=( type=virt )
		;;
	esac

	qmachine+=( accel=kvm )

	if [[ ${debug} ]]; then
		kcmds+=( rd.debug )
		kcmds+=( systemd.log_level=debug )
	fi

	if [[ ${q_gdb} ]]; then
		# -s: makes gdb be able to attach through localhost:1234
		# -S: stops qemu waiting gdb
		qargs+=( -s -S )
	fi
}

config_memory() {
	local m=( ${q_memory} )
	m+=( slots=8 )
	m+=( maxmem=32768M )
	qargs+=( -m $(IFS=,; echo "${m[*]}") )
}

# $1: require memory size
min_memory_required() {
	local reqsz=$1
	if [[ $(size2bytes ${q_memory}) -lt $(size2bytes ${reqsz}) ]]; then
		error "Need memory size ${reqsz} at least, but it's ${q_memory}"
	fi
}

config_cpu() {
	qargs+=( -cpu host -smp cpus=4 )
}

config_uefi() {
	local i code var
	local codes=( /usr/share/OVMF/OVMF_CODE.fd )
	local vars=( /usr/share/OVMF/OVMF_VARS.fd )

	case ${arch} in
	aarch64)
		codes+=( /usr/share/edk2/aarch64/QEMU_EFI-silent-pflash.raw )
		vars+=( /usr/share/edk2/aarch64/QEMU_VARS.fd )
		;;
	esac

	# FIXME: aarch64 default UEFI, skip error:
	# qemu-kvm: device requires 67108864 bytes, block backend provides 786432 bytes
	if [[ ${arch} == aarch64 ]]; then
		return 0
	fi

	for i in ${codes[@]}; do
		if [[ -e ${i} ]]; then
			code=${i}
			break
		fi
	done

	for i in ${vars[@]}; do
		if [[ -e ${i} ]]; then
			var=${i}
			break
		fi
	done

	if [[ -z ${code} ]]; then
		error "not found ovmf code: ${codes[@]}"
	fi

	qargs+=( -drive if=pflash,format=raw,readonly=on,file=${code} )
	if [[ ${var} ]]; then
		qargs+=( -drive if=pflash,format=raw,file=${var} )
	fi
}

config_pci() {
	local i args

	# Config pcie-root-port
	for i in $(seq 1 ${pcie_root_port_num}); do
		unset args
		args+=( bus=${bus_pcie0} )
		args+=( id=pcie.${i} )
		args+=( chassis=${i} )
		args+=( port=${i} )
		qargs+=( -device pcie-root-port,$(IFS=,; echo "${args[*]}") )
	done
}

add_net_nic_user() {
	qargs+=(-netdev type=user,id=net0
		-device virtio-net-pci,bus=${bus_pcie0},netdev=net0,addr=6.0 )
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
# $ ssh -p8086 root@localhost
# Make sure port was not used, check with:
# $ sudo netstat -tulpn | grep 8086
add_net_nic_user_tap() {
	qargs+=( -net user,hostfwd=tcp::8086-:22
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
	kcmds+=( selinux=0 audit=0 nokaslr )
	case ${arch} in
	aarch64)
		kcmds+=( console=ttyAMA0 )
		;;
	*)
		kcmds+=( console=tty0 console=ttyS0 )
		;;
	esac

	if [[ ${k_rdinit} ]]; then
		kcmds+=( rdinit=${k_rdinit} )
	fi
	if [[ ${k_init} ]]; then
		kcmds+=( init=${k_init} )
	fi
}

add_virtio_disk() {
	local f_img=$1
	local f_type=${f_img##*.}
	local virtio_id=$(mktemp -u virtio-XXXXXX)
	qargs+=( -drive file=${f_img},format=${f_type},if=none,id=${virtio_id}
		-device virtio-blk,drive=${virtio_id} )
}
add_sata_disk() {
	local f_img=$1
	local f_type=${f_img##*.}
	local sata_id=$(mktemp -u sata-XXXXXX)
	qargs+=( -device ahci,id=ahci0
		-drive if=none,file=${f_img},format=${f_type},id=${sata_id}
		-device ide-hd,bus=ahci0.0,drive=${sata_id} )
}
add_nvme_disk() {
	local f_img=$1
	local f_type=${f_img##*.}
	local drive_id=$(mktemp -u nvme-XXXXXX)
	qargs+=( -drive if=none,file=${f_img},format=${f_type},id=${drive_id}
		-device nvme,drive=${drive_id},serial=sn-${drive_id} )
}

add_scsi_disk() {
	local f_img=$1
	local f_type=${f_img##*.}
	local hd_id=$(mktemp -u hd-XXXXXX)
	qargs+=( -device virtio-scsi-pci,id=scsi0
		-device scsi-hd,drive=${hd_id}
		-drive file=${f_img},if=none,aio=native,cache=none,format=${f_type},id=${hd_id} )
}

add_nvdimm_blk() {
	local size nv_id obj_id f_img

	f_img=${1}
	qmachine+=( nvdimm=on )

	size=$(stat --format=%s ${f_img})
	skip_resize() {
		if [[ ${size} -lt $((1024*1024*1024)) ]]; then
			size=$((1024*1024*1024))
		fi
	}
	obj_id=$(mktemp -u nvdimm-XXXXXX)
	nv_id=$(mktemp -u nv-XXXXXX)

	qargs+=( -device nvdimm,id=${nv_id},memdev=${obj_id},unarmed=on )
	qargs+=( -object memory-backend-file,id=${obj_id},mem-path=${f_img},size=${size},readonly=on )
}

config_rootfs() {
	if [[ -z ${f_rootfs} ]]; then
		# if not rootfs, we should break in initrd.
		kcmds+=( rd.break ) # dracut.cmdline(7)
		return 0
	fi

	case ${f_rootfs_disk_type} in
	${DISK_TYPE_VIRTIO}) add_virtio_disk ${f_rootfs} ;;
	${DISK_TYPE_SATA}) add_sata_disk ${f_rootfs} ;;
	${DISK_TYPE_NVME}) add_nvme_disk ${f_rootfs} ;;
	${DISK_TYPE_NVDIMM}) add_nvdimm_blk ${f_rootfs} ;;
	${DISK_TYPE_SCSI}) add_scsi_disk ${f_rootfs} ;;
	esac

	kcmds+=( ${k_rw} )

	if [[ ${k_root} ]]; then
		kcmds+=( root=${k_root} )
	else
		kcmds+=( root=UUID=$(image2uuid ${f_rootfs}) )
	fi
}

config_nvdimm() {

	if [[ -z ${f_nvdimm} ]]; then
		return 0
	fi

	add_nvdimm_blk ${f_nvdimm}
}

__pxb_cxl_id_file=$(mktemp -u)
cleanup_files+=( ${__pxb_cxl_id_file} )
next_pxb_cxl_id() {
	local num=1
	if [[ -f ${__pxb_cxl_id_file} ]]; then
		num=$(cat ${__pxb_cxl_id_file})
	fi
	echo "pxbcxl.${num}"
	echo $((++num)) > ${__pxb_cxl_id_file}
}

# bus_nr=11,21,31,41,...
__pxb_cxl_bus_nr_file=$(mktemp -u)
cleanup_files+=( ${__pxb_cxl_bus_nr_file} )
next_pxb_cxl_bus_nr() {
	local num=11
	if [[ -f ${__pxb_cxl_bus_nr_file} ]]; then
		num=$(cat ${__pxb_cxl_bus_nr_file})
	fi
	echo "${num}"
	echo $((num + 10)) > ${__pxb_cxl_bus_nr_file}
}

__cxl_rp_id_file=$(mktemp -u)
cleanup_files+=( ${__cxl_rp_id_file} )
next_cxl_rp_id() {
	local num=1
	if [[ -f ${__cxl_rp_id_file} ]]; then
		num=$(cat ${__cxl_rp_id_file})
	fi
	echo "cxl.rp.${num}"
	echo $((++num)) > ${__cxl_rp_id_file}
}

add_cxl_pxb() {
	local id=$1
	qargs+=( -device pxb-cxl,bus_nr=$(next_pxb_cxl_bus_nr),bus=${bus_pcie0},id=${id} )
}

# root port
# $1: bus
# $2: id
# $3: port (slot if $4 is empty)
# $4: slot
add_cxl_rp() {
	local bus=$1
	local id=$2
	local port=$3
	local slot=${4-${port}}
	local arg

	arg+=( cxl-rp )
	arg+=( port=${port} )
	arg+=( bus=${bus} )
	arg+=( id=${id} )
	arg+=( chassis=0 )
	arg+=( slot=${slot} )

	qargs+=( -device $(IFS=,; echo "${arg[*]}") )
}

# A setup suitable for multi ways interleave. Only one fixed window provided, to
# enable multi ways interleave across 2 CXL host bridges. Each host bridge has 2
# CXL Root Ports, with the CXL Type3 device directly attached (no switches).
__cxl_pmem_ways() {
	local i ways=${1}

	# TODO: Why cxl pmem 4way need higher ram memory than CXL Type3?
	min_memory_required $((${ways} + 1))G

	local pxb_cxl_id1=$(next_pxb_cxl_id)
	local pxb_cxl_id2=$(next_pxb_cxl_id)

	add_cxl_pxb ${pxb_cxl_id1}
	add_cxl_pxb ${pxb_cxl_id2}

	for ((i = 1; i <= ${ways}; i++))
	do
		local tmparg lsa mem

		mem=cxl-mem${i}
		lsa=cxl-lsa${i}

		_eval qemu-img create -f raw cxltest${i}.raw ${cxl_size}
		_eval qemu-img create -f raw lsa${i}.raw ${cxl_size}
		cleanup_files+=( cxltest${i}.raw lsa${i}.raw )

		tmparg+=( memory-backend-file,id=${mem} )
		tmparg+=( share=on )
		tmparg+=( mem-path=$PWD/cxltest${i}.raw )
		tmparg+=( size=${cxl_size} )
		qargs+=( -object $(IFS=,; echo "${tmparg[*]}") )
		unset tmparg

		tmparg+=( memory-backend-file,id=${lsa} )
		tmparg+=( share=on )
		tmparg+=( mem-path=$PWD/lsa${i}.raw )
		tmparg+=( size=${cxl_size} )
		qargs+=( -object $(IFS=,; echo "${tmparg[*]}") )
		unset tmparg

		local rp_id=$(next_cxl_rp_id)
		add_cxl_rp ${pxb_cxl_id1} ${rp_id} ${i}

		# Or could add it to CXL switch
		local cxl_dev_bus=${rp_id}

		tmparg+=( cxl-type3,bus=${cxl_dev_bus} )
		tmparg+=( persistent-memdev=${mem} )
		tmparg+=( lsa=${lsa} )
		tmparg+=( id=cxl-pmem${i} )
		tmparg+=( sn=0x${i} )
		qargs+=( -device $(IFS=,; echo "${tmparg[*]}") )
		unset tmparg
	done

	qmachine+=( cxl-fmw.0.targets.0=${pxb_cxl_id1} )
	qmachine+=( cxl-fmw.0.targets.1=${pxb_cxl_id2} )
	qmachine+=( cxl-fmw.0.size=4G )
	qmachine+=( cxl-fmw.0.interleave-granularity=8k )
}

cxl_pmem() {
	__cxl_pmem_ways 1
}

cxl_pmem_4way() {
	__cxl_pmem_ways 4
}

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

	add_cxl_pxb cxl.1

	local rp_id1=$(next_cxl_rp_id)
	local rp_id2=$(next_cxl_rp_id)

	add_cxl_rp cxl.1 ${rp_id1} 0
	add_cxl_rp cxl.1 ${rp_id2} 1

	qargs+=( -device cxl-upstream,bus=${rp_id1},id=us0 )

	qmachine+=( cxl-fmw.0.targets.0=cxl.1 )
	qmachine+=( cxl-fmw.0.size=4G )
	qmachine+=( cxl-fmw.0.interleave-granularity=4k )

	for i in $(seq 0 1 3)
	do
		qargs+=( -device cxl-downstream,port=${i},bus=us0,id=swport${i},chassis=0,slot=$((${i}+2))
			-device cxl-type3,bus=swport${i},persistent-memdev=cxl-mem${i},lsa=cxl-lsa${i},id=cxl-pmem${i},sn=0x1
			)
	done
}

__cxl_volatile_mem_lsa() {
	local LSA

	qargs+=(-object memory-backend-ram,id=vmem0,share=on,size=${cxl_size})

	if [[ ${1} == lsa ]]; then
		_eval qemu-img create -f raw lsa.raw ${cxl_size}
		cleanup_files+=( lsa.raw )
		LSA="lsa=cxl-lsa0,"
		qargs+=(-object memory-backend-file,id=cxl-lsa0,share=on,mem-path=$PWD/lsa.raw,size=${cxl_size})
	fi

	add_cxl_pxb cxl.1

	local rp_id=$(next_cxl_rp_id)

	add_cxl_rp cxl.1 ${rp_id} 2

	qargs+=( -device cxl-type3,bus=${rp_id},volatile-memdev=vmem0,${LSA}id=cxl-vmem0 )

	qmachine+=( cxl-fmw.0.targets.0=cxl.1 )
	qmachine+=( cxl-fmw.0.size=4G )
}

cxl_volatile_mem() {
	__cxl_volatile_mem_lsa
}

cxl_volatile_mem_lsa() {
	__cxl_volatile_mem_lsa lsa
}

cxl_volatile_mem_4way() {
	local i

	add_cxl_pxb cxl.1

	for i in {1..4}
	do
		local rp_id=$(next_cxl_rp_id)

		add_cxl_rp cxl.1 ${rp_id} ${i}

		qargs+=( -object memory-backend-ram,id=vmem${i},share=on,size=${cxl_size}
			-device cxl-type3,bus=${rp_id},volatile-memdev=vmem${i},id=cxl-vmem${i} )
	done

	qmachine+=( cxl-fmw.0.targets.0=cxl.1 )
	qmachine+=( cxl-fmw.0.size=4G )
}

cxl_volatile_mem_4way_switch() {
	for i in $(seq 0 1 3)
	do
		qargs+=( -object memory-backend-ram,id=vmem${i},share=on,size=${cxl_size}
			)
	done

	add_cxl_pxb cxl.1

	local rp_id1=$(next_cxl_rp_id)
	local rp_id2=$(next_cxl_rp_id)
	add_cxl_rp cxl.1 ${rp_id1} 0
	add_cxl_rp cxl.1 ${rp_id2} 1

	qargs+=( -device cxl-upstream,bus=${rp_id1},id=us0 )

	qmachine+=( cxl-fmw.0.targets.0=cxl.1 )
	qmachine+=( cxl-fmw.0.size=4G )
	qmachine+=( cxl-fmw.0.interleave-granularity=4k )

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
	local i

	if [[ ! -z "${cxl_device}${cxl_pxb_ids}" ]] && [[ ${debug} ]]; then
		cxl_debug
	fi

	if [[ ! -z "${cxl_device}${cxl_pxb_ids}" ]]; then
		qmachine+=( cxl=on )
		# Disable ACPI CXL enumeration at boot
		# kcmds+=( acpi=off )
		kcmds+=( cxl.mem=disable cxl.acpi=0 )
	fi

	# Create CXL PXB
	for i in ${cxl_pxb_ids[@]}
	do
		add_cxl_pxb $i
	done

	# Create CXL RootPort
	for ((i = 0; i < ${#cxl_rp_ids[@]}; i++))
	do
		add_cxl_rp ${cxl_rp_buss[i]} ${cxl_rp_ids[i]} \
			   ${cxl_rp_ports[i]} ${cxl_rp_slots[i]}
	done

	case ${cxl_device} in
	${CXL_DEV_PMEM})
		cxl_pmem
		;;
	${CXL_DEV_PMEM_4WAY})
		cxl_pmem_4way
		;;
	${CXL_DEV_PMEM_4WAY_SWITCH})
		cxl_pmem_4way_switch
		;;
	${CXL_DEV_VOLATILE_MEM})
		cxl_volatile_mem
		;;
	${CXL_DEV_VOLATILE_MEM_LSA})
		cxl_volatile_mem_lsa
		;;
	${CXL_DEV_VOLATILE_MEM_4WAY})
		cxl_volatile_mem_4way
		;;
	${CXL_DEV_VOLATILE_MEM_4WAY_SWITCH})
		cxl_volatile_mem_4way_switch
		;;
	esac
}

config_virtiofs() {
	if [[ -z ${f_virtiofs_sock} ]] && [[ -z ${q_virtiofs_tag} ]]; then
		return
	fi

	if [[ -z ${f_virtiofs_sock} ]] || [[ -z ${q_virtiofs_tag} ]]; then
		error "Must specify --virtio-fs-sock and --virtio-fs-tag at the same time"
	fi

	# ref: https://qemu-stsquad.readthedocs.io/en/doc-updates/tools/virtiofsd.html
	qargs+=(-chardev socket,id=char0,path=${f_virtiofs_sock}
		-device vhost-user-fs-pci,chardev=char0,bus=${bus_pcie0},tag=${q_virtiofs_tag}
		-object memory-backend-memfd,id=mem,size=${q_memory},share=on
		-numa node,memdev=mem )
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
config_virtiofs

qmachine=( $(printf "%s\n" ${qmachine[@]} | sort -u) )
qargs+=( -machine $(IFS=,; echo "${qmachine[*]}") )

_eval ${QEMU_KVM} ${qargs[@]} -append \"${kcmds[@]}\"
