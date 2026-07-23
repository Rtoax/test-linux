#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
#
# Use the qemu command to create a virtual machine directly, without using
# libvirt, but directly use the qemu command line parameters.
#
# Copyright (C) 2025-2026 Rong Tao
#
set -e

readonly QEMU_VM_ROOT=$(dirname $(realpath $0))

. ${QEMU_VM_ROOT}/libfile.sh
. ${QEMU_VM_ROOT}/liblog.sh
. ${QEMU_VM_ROOT}/libqemu.sh
. ${QEMU_VM_ROOT}/libstring.sh

readonly PROG=qemu-vm
readonly arch=$(uname -m)
QEMU_KVM=$(get_qemu_kvm_emulator)

readonly BUS_PCIE0=pcie.0 # q35 default root bus
pcie_root_port_num=2

q_vm_name=$(mktemp -u vm-XXXXXX)
q_cpus=4
q_memory=2G

f_kernel=
f_initrd=
k_rdinit=

f_rootfs=
f_rootfs_type=
k_init=
k_root=
# root mount attr: ro, rw. default: rw
k_rw=rw

declare -a f_nvdimms

# Disk shoud contains boot(EFI) partition, kernel, initramfs, etc.
declare -a f_disks

declare -a f_virtiofs_sock
declare -a q_virtiofs_tag

q_stdio=
q_monitor=
readonly q_monitor_telnet_port=8087
q_gdb=

dry_run=
verbose=
version="v1.0.1"
debug=

# Disk configuratios
readonly DISK_VIRTIO=virtio
readonly DISK_SATA=sata
readonly DISK_NVME=nvme
readonly DISK_NVDIMM=nvdimm
readonly DISK_SCSI=scsi
readonly DISK_TYPES=( ${DISK_VIRTIO} ${DISK_SATA} ${DISK_NVME} ${DISK_SCSI}
		      ${DISK_NVDIMM} )

declare -a qargs qmachine kcmds
declare -a cleanup_files

readonly FORMAT_SIZE="${UL}SIZE${RST}: B, K, KB, KiB, M, MB, MiB, G, GB, GiB"

__usage__() {
	echo -e "
${BOLD}NAME${RST}
    ${PROG} - Running a virtual machine with Qemu-KVM

${BOLD}SYNOPSIS${RST}
    ${PROG} -k=<kernel> -i=<initrd> [-r=<rootfs>] [-m=4G] [--stdio] [--monitor]

${BOLD}DESCRIPTION${RST}
    Running a virtual machine with Qemu-KVM, support flexable arguments.

${BOLD}OPTIONS${RST}
    -n, --name [NAME]       specify vm name, default: vm- prefix

    --cpu [ARGS]            config CPU, please see ${BOLD}--cpu help${RST}
    -m, --memory [SIZE]     Sets guest startup RAM size, default: ${q_memory},
                            format see ${UL}SIZE${RST} section.

    -k, --kernel [KERNEL]   specify vmlinuz, bzImage
        --kcmd [ARG]        add kernel cmdline (may be listed multiple times)
                            example: --kcmd=${GRAY}rdinit=/usr/bin/bash${RST}

    -i, --initrd [INITRD]   specify initrd image
        --rdinit [PATH]     specify initrd's init process.

    -r, --rootfs [type=TYPE,file=ROOTFS,<rw|ro>]|[ROOTFS]
                            optional specify rootfs image.
                            TYPE=\"${DISK_TYPES[@]}\"
        --init [PATH]       specify rootfs's init process.
        --root [ROOT]       specify root= in kernel cmdline, default use UUID
                            of rootfs image.

    -d, --disk [ARGS]       add a disk. please see ${BOLD}--disk help${RST}

    --nvdimm [FILE]         add a nvdimm pmem (may be listed multiple times)

    --stdio                 input/output from/to stdio. Default ${GRAY}TERM=${RST}${UL}vt220${RST}
                            if stdio, you could set ${UL}TERM=xterm-256color${RST}
                            or ${UL}TERM=linux${RST} in your virtual machine.

    --monitor               enable monitor, link with ${GRAY}$ telnet localhost ${q_monitor_telnet_port}${RST}

  ${BOLD}VirtIO OPTIONS${RST}
    --virtio-fs-sock [SOCK] specify virtio-fs vhost-fs.sock, this sock created
                            by ${GRAY}$ virtiofsd --socket-path=/var/run/vhost-fs.sock -o source=/path/to/host/${RST}
                            (may be listed multiple times)
    --virtio-fs-tag [TAG]   specify virtio-fs tag, like: ${GRAY}${UL}myfs${RST}, then,
                            in guest os: ${GRAY}$ sudo mount -t virtiofs ${UL}myfs${RST} ${GRAY}/mnt${RST}
                            (may be listed multiple times)

  ${BOLD}UEFI OPTIONS${RST}
    --uefi [ARGS]           UEFI by Qemu. please see ${BOLD}--uefi help${RST}

  ${BOLD}QEMU OPTIONS${RST}
    -Q, --qemu [qemu-kvm]   specify qemu emulator binary.
        --gdb               enable qemu debugging, usage:${GRAY}
                            $ gdb -q kernel.elf
                            (gdb) target remote :1234
                            (gdb) hbreak start_kernel
                            (gdb) continue${RST}
                            the ${UL}kernel.elf${RST} also could get:${GRAY}
                            $ objcopy --only-keep-debug vmlinux kernel.elf${RST}

    --qarg [ARG]            append ARG to qemu arguments, for example:
                            pass ${BOLD}-fw_cfg${RST} to qemu:
                              ${GRAY}-fw_cfg [name=]<name>,file=<file>${RST}
                              ${GRAY}-fw_cfg [name=]<name>,[name=]<name>,string=<str>${RST}
                            you could:
                              ${GRAY}$ ${PROG} --qarg \"-fw_cfg name=${USER},file=/etc/os-release\"${RST}
                            in guest, check ${BOLD}/sys/firmware/qemu_fw_cfg/${RST}
                            (may be listed multiple times)

  ${BOLD}CXL OPTIONS${RST}
    --cxl [ARGS]            CXL by Qemu. please see ${BOLD}--cxl help${RST}

                            CXL require Qemu >= ${UL}9.0${RST} on aarch64,
                            Qemu >= ${UL}7.2${RST} on x86_64.

  ${BOLD}COMMON OPTIONS${RST}
    -u, --dry-run           only show commands
    -D, --debug             enable debug mode.
    -v, --verbose           enable verbose mode.
    -V, --version           show version
    -h, --help              show this help information

${BOLD}EXAMPLES${RST}
    $ sudo ${PROG} --kernel ${GRAY}${ITALIC}/boot/vmlinuz-${arch}${RST} \\
        --initrd ${GRAY}${ITALIC}/boot/initramfs-${arch}.img${RST} ${GRAY}[--rdinit=/bin/bash]${RST} \\
        ${GRAY}[--rootfs vm.raw] [--init=/usr/bin/bash]${RST}

${BOLD}FORMAT${RST}

  ${FORMAT_SIZE}

${BOLD}SEE ALSO${RST}
    qemu(1), qemu-kvm(1), etc.
"
	exit ${1-0}
}

check_files_exist_and_exit() {
	local f
	for f in ${@}
	do
		if [[ ! -e ${f} ]] && [[ -z ${dry_run} ]]; then
			error "${f} is not exist."
		fi
	done
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
	if [[ $(is_qemu_format ${f_rootfs}) != yes ]] && [[ -z ${dry_run} ]]; then
		error "${f_rootfs} is not raw or qcow2."
	fi
}

################################################################################
# CPU

cpu_arg_help() {
	echo -e "
${BOLD}CPU ARGUMENTS SYNTAX${RST}

${BOLD}--cpu help${RST}: show this information

${BOLD}--cpu [num]${RST}: set cpu number
${BOLD}--cpu nr=[num]${RST}: set cpu number
"
	exit 0
}

handle_cpu_arg() {
	local arg args
	local nr_cpus

	# Pre handle
	args=( $(echo $1 | tr ',' ' ') )
	for arg in ${args[@]}
	do
		case ${arg%%=*} in
		help)
			cpu_arg_help
			;;
		esac
	done
	unset args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -gt 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			nr)
				nr_cpus=${arg:3}
				;;
			*)
				error "cpu unknown arg ${arg}"
				;;
			esac
		done
	else
		nr_cpus=$1
	fi

	q_cpus=${nr_cpus}
}

################################################################################
# UEFI
declare -a UEFI_CODES=(
	# OVMF: Open Virtual Machine Firmware
	/usr/share/OVMF/OVMF_CODE.fd
	/usr/share/AAVMF/AAVMF_CODE.fd
)

declare -a UEFI_VARS=(
	/usr/share/OVMF/OVMF_VARS.fd
	/usr/share/AAVMF/AAVMF_VARS.fd
)

case ${arch} in
aarch64)
	UEFI_CODES+=( /usr/share/edk2/aarch64/QEMU_EFI-silent-pflash.raw )
	UEFI_VARS+=( /usr/share/edk2/aarch64/QEMU_VARS.fd )
	;;
esac

declare uefi_code uefi_var
declare uefi_novar

uefi_arg_help() {
	echo -e "
${BOLD}UEFI ARGUMENTS SYNTAX${RST}

${BOLD}--uefi help${RST}: show this information

${BOLD}--uefi code=<FILE>${RST}: specify code, such as: ${UEFI_CODES[@]}
${BOLD}--uefi var=<FILE>${RST}: specify var, such as: ${UEFI_VARS[@]}, only specify if 'code' specified. This is usually NVRAM.
${BOLD}--uefi novar${RST}: disable VARS
"
	exit 0
}

handle_uefi_arg() {
	local arg args code var

	# Pre handle
	args=( $(echo $1 | tr ',' ' ') )
	for arg in ${args[@]}
	do
		case ${arg%%=*} in
		help)
			uefi_arg_help
			;;
		esac
	done
	unset args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -ge 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			code)
				code=${arg:5}
				;;
			var)
				var=${arg:4}
				;;
			novar)
				uefi_novar=ON
				;;
			*)
				error "uefi unknown ${arg}"
				;;
			esac
		done
	fi

	if [[ ${var} ]] && [[ ${code} ]]; then
		error "--uefi could not specify code and var at the same time."
	fi

	[[ ${code} ]] && check_files_exist_and_exit ${code}
	[[ ${var} ]] && check_files_exist_and_exit ${var}

	[[ ${code} ]] && uefi_code=${code}
	[[ ${var} ]] && uefi_var=${var}

	if [[ ${uefi_novar} ]] && [[ ${uefi_var} ]]; then
		error "--uefi could not specify var and novar at the same time"
	fi
}

################################################################################
# Rootfs

# Format: type=TYPE,file=FILE,ro,rw
handle_rootfs_arg() {
	local arg args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -gt 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			type)
				f_rootfs_type=${arg:5}
				if ! [[ " ${DISK_TYPES[@]} " =~ " ${f_rootfs_type} " ]]; then
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

	if [[ -z ${f_rootfs_type} ]]; then
		f_rootfs_type=${DISK_VIRTIO}
	fi
}

disk_arg_help() {
	echo -e "
${BOLD}DISK ARGUMENTS SYNTAX: -d, --disk <ARGS>${RST}

${BOLD}ARGS${RST}
  ${BOLD}help${RST}: show this information

  ${BOLD}[FILE]${RST}: specify disk file, see ${BOLD}[FILE]${RST}
  ${BOLD}file=<FILE>${RST}: specify disk file, see ${BOLD}[FILE]${RST}

${BOLD}FILE${RST}: disk file, should be one of qcow2, raw, MBR
"
	exit 0
}

handle_disk_arg() {
	local arg args
	local file

	# Pre handle
	args=( $(echo $1 | tr ',' ' ') )
	for arg in ${args[@]}
	do
		case ${arg%%=*} in
		help)
			disk_arg_help
			;;
		esac
	done
	unset args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -gt 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			file)
				file=${arg:5}
				;;
			*)
				error "--disk unknown arg ${arg}"
				;;
			esac
		done
	else
		file=$1
	fi

	if [[ -z ${file} ]]; then
		error "--disk must specify disk file"
	fi

	f_disks+=( ${file} )
}

################################################################################
# CXL
# ===
# - CXL level: pxb-cxl -> cxl-rp -> cxl-switch/cxl-type3
#   pxb: PCIe eXpander Bridge
#   rp: Root Port
# - CXL fmw: Fixed Memory Window
#
#       ┌────────────────────────────┐
#       │    PCIe.0(q35)             │
#       │     ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐    │
#       └─────┴─┴─┴─┴─┴┬┴─┴─┴─┴─┴────┘
#                      │
#                      │
#       ┌─────────────┬┴┬────────────┐
#       │   PXB CXL   └─┘            │
#       │     ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐    │
#       └─────┴┬┴─┴─┴─┴─┴─┴─┴─┴┬┴────┘
#              │               └──┐
#              │                  │
#       ┌─────┬┴┬───┐      ┌─────┬┴┬───┐
#       │     └─┘   │      │     └─┘   │
#       │ Root Port │      │ Root Port │
#       │     ┌─┐   │      │     ┌─┐   │
#       └─────┴┬┴───┘      └─────┴┬┴───┘
#              │                  │
#              │                  │
#           UP │     upstream     │
# ┌───────────┬┼┬───────────┐     │
# │CXL Switch └┴┘           │     │
# │ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ │     │
# └─┴─┴─┴─┴─┴┬┴─┴─┴─┴─┴─┴─┴─┘     │
#    D1  D2  │3  D4  D5  D6       │
#            │     downstream     │
#            │                    │
#            │                    │
#         ┌──┴──────┐        ┌────┴────┐
#         │CXL Type3│        │CXL Type3│
#         └─────────┘        └─────────┘
#
# - Refs:
#   https://www.qemu.org/docs/master/system/devices/cxl.html
readonly CXL_DEV_VMEM=cxl-vmem
readonly CXL_DEV_VMEM_LSA=cxl-vmem-lsa
readonly CXL_DEV_VMEM_4WAY=cxl-vmem-4way
readonly CXL_DEV_VMEM_4WAY_SWITCH=cxl-vmem-4way-switch
readonly CXL_DEV_PMEM=cxl-pmem
readonly CXL_DEV_PMEM_4WAY=cxl-pmem-4way
readonly CXL_DEV_PMEM_4WAY_SWITCH=cxl-pmem-4way-switch
readonly CXL_DEVICES=( ${CXL_DEV_VMEM} ${CXL_DEV_VMEM_LSA}
			${CXL_DEV_VMEM_4WAY} ${CXL_DEV_VMEM_4WAY_SWITCH}
			${CXL_DEV_PMEM} ${CXL_DEV_PMEM_4WAY} ${CXL_DEV_PMEM_4WAY_SWITCH})

declare -a cxl_fmw=( 0 ) # (0 1 2 3)

# cxl-pxb specify id=, this is CHBS(CXL Host Bridge Structure)
# and use to -machine cxl-fmw.0.targets.M
declare -a cxl_pxb_ids # ( pxb-id1 pxb-id2 ... )
declare -A cxl_pxb_fmw # arr[pxb-id]=0, default is 0
declare -A cxl_pxb_sizes # arr[pxb-id]=2G
declare -A cxl_pxb2rps # arr[pxb-id]="rp-id1 rp-id2 ..."

# cxl root port
declare -a cxl_rp_ids cxl_rp_buss cxl_rp_ports
# use to find root port's pxb with rp-id
declare -A cxl_rp2pxb # arr[rp-id1]=pxb-id1
declare -A cxl_rp2swup # arr[rp-id]=switch-upstream-id
declare -A cxl_rp2pvmem # arr[rp-id]=pmem-id|vmem-id

# cxl switch
# cxl switch bus (rootport)
declare -a cxl_switches_bus # ( rp-id1 rp-id2 ... )
# cxl switch downstream port number
declare -a cxl_switches_ndport # ( 2 3 ... )
# cxl switch downstream port id prefix
declare -a cxl_switches_dportpfx # ( name1 name2 ... )
# cxl switch upstream id to root port id
declare -A cxl_switch_up2rp # arr[switch-upstream-id]=rp-id
declare -A cxl_switch_up2downs # arr[up-id]="down-id id2 id3 ..."
# cxl switch downstream id to upstream id
declare -A cxl_switch_down2up # arr[downstream-id]=upstream-id
declare -A cxl_switch_down2pvmem # arr[downstream-id]=type3-id

# cxl type3 devices
declare -a cxl_pmem_names # arr=( name1 name2 ... )
declare -A cxl_pmem_bus # arr[name]=BUS
declare -A cxl_pmem_lsa # arr[name]=LSA
declare -A cxl_pmem_size # arr[name]=SIZE
declare -a cxl_vmem_names # arr=( name1 name2 ... )
declare -A cxl_vmem_bus # arr[name]=BUS
declare -A cxl_vmem_lsa # arr[name]=LSA
declare -A cxl_vmem_size # arr[name]=SIZE
# use to find root port id or switch downstream id of cxl-type3
declare -A cxl_pvmem_id2bus # arr[type3-id]=[rp-id|switch-downstream-id]
declare -A cxl_pvmem_id2name # arr[type3-id]=NAME in cxl_pmem_names[]
declare -a cxl_pvmem_ids # ( id1 id2 ... )

declare cxl_device
readonly CXL_DEFAULT_MSIZE=1024M
# display cxl device topology before vm startup
declare cxl_show_topology

cxl_arg_help() {
	echo -e "
${BOLD}CXL ARGUMENTS SYNTAX${RST}

${BOLD}--cxl help${RST}: show this information

${BOLD}--cxl [DEV]${RST}: see ${BOLD}[DEV]${RST} below
${BOLD}--cxl device=[DEV]${RST}

${BOLD}--cxl pxb=<name>,[fmw=<N>]${RST}: create CXL PXB, fmw default 0
${BOLD}--cxl rp=<name>,bus=<name>,port=<n>${RST}: create CXL RootPort
${BOLD}--cxl switch,bus=<name>,nport=<n>,portprefix=<name>${RST}: create CXL Switch
${BOLD}--cxl pmem=<name>,bus=<name>,lsa=<name>,[size=<SIZE>]${RST}: create CXL Persistent Memory device
${BOLD}--cxl vmem=<name>,bus=<name>,[lsa=<name>][size=<SIZE>]${RST}: create CXL Volatile Memory device

${BOLD}--cxl show=[topo]${RST}: display CXL information before vm startup, will not startup vm

${BOLD}[DEV]${RST}
${GRAY}${CXL_DEVICES[@]}${RST}

${BOLD}FORMAT${RST}

  ${FORMAT_SIZE}
"
	exit 0
}

# Formats: device=<name>
handle_cxl_arg() {
	local arg args
	local device
	local pxb_id pxbfmw=0
	local bus port
	local rp_id
	local switch nport portprefix
	local pmem vmem lsa size

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
			fmw)
				pxbfmw=${arg:4}
				if ! [[ " 0 1 2 3 4 5 " =~ " ${pxbfmw} " ]]; then
					error "bad cxl pxb ${arg} only support 0 1 2 3 4 5"
				fi
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
			switch)
				switch=ON
				;;
			nport)
				nport=${arg:6}
				[[ -z ${nport} ]] && \
					error "cxl switch nport= syntax error"
				;;
			portprefix)
				portprefix=${arg:11}
				[[ -z ${portprefix} ]] && \
					error "cxl switch portprefix= syntax error"
				;;
			pmem)
				pmem=${arg:5}
				[[ -z ${pmem} ]] && \
					error "cxl pmem= syntax error"
				;;
			vmem)
				vmem=${arg:5}
				[[ -z ${vmem} ]] && \
					error "cxl vmem= syntax error"
				;;
			lsa)
				lsa=${arg:4}
				[[ -z ${lsa} ]] && \
					error "cxl lsa= syntax error"
				;;
			size)
				size=${arg:5}
				[[ -z ${size} ]] && \
					error "cxl size= syntax error"
				;;
			show)
				case ${arg:5} in
				topo)
					cxl_show_topology=ON
					;;
				*)
					error "--cxl show= syntax"
					;;
				esac
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

	if [[ ${device} ]] && [[ ${switch} ]]; then
		error "--cxl not allow specify switch for device"
	fi

	if [[ ${device} ]] && [[ ${pmem}${vmem} ]]; then
		error "--cxl not allow specify pmem or vmem for device"
	fi

	local types=( ${pxb_id} ${rp_id} ${switch} ${vmem} ${pmem} )

	if [[ ${#types[@]} -gt 1 ]]; then
		error "--cxl not allow specify pxb,rp,switch,vmem,pmem at the same time"
	fi

	if [[ ${rp_id} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${port} ]]; then
			error "--cxl rp need bus= port= at the same time"
		fi
	fi

	if [[ ${switch} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${nport} ]] || [[ -z ${portprefix} ]]; then
			error "--cxl switch need bus= nport= portprefix= at the same time"
		fi
	fi

	if [[ ${pmem} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${lsa} ]]; then
			error "--cxl pmem/vmem need bus= and lsa= parameter"
		fi
	fi

	if [[ ${vmem} ]]; then
		if [[ -z ${bus} ]]; then
			error "--cxl vmem need bus= parameter"
		fi
	fi

	# set global
	[[ ${device} ]] && cxl_device=${device}
	if [[ ${pxb_id} ]]; then
		cxl_pxb_ids+=( ${pxb_id} )
		cxl_pxb_fmw[$pxb_id]=${pxbfmw}
	fi

	if [[ ${rp_id} ]]; then
		cxl_rp_ids+=( ${rp_id} )
		[[ ${bus} ]] && cxl_rp_buss+=( ${bus} )
		[[ ${port} ]] && cxl_rp_ports+=( ${port} )
	fi

	if [[ ${switch} ]]; then
		cxl_switches_bus+=( ${bus} )
		cxl_switches_ndport+=( ${nport} )
		cxl_switches_dportpfx+=( ${portprefix} )
	fi

	if [[ ${pmem} ]]; then
		cxl_pmem_names+=( ${pmem} )
		cxl_pmem_bus[$pmem]=${bus}
		[[ -z ${lsa} ]] && lsa=SKIP
		cxl_pmem_lsa[$pmem]=${lsa}
		[[ -z ${size} ]] && size=${CXL_DEFAULT_MSIZE}
		cxl_pmem_size[$pmem]=${size}
	fi

	if [[ ${vmem} ]]; then
		cxl_vmem_names+=( ${vmem} )
		cxl_vmem_bus[$vmem]=${bus}
		[[ -z ${lsa} ]] && lsa=SKIP
		cxl_vmem_lsa[$vmem]=${lsa}
		[[ -z ${size} ]] && size=${CXL_DEFAULT_MSIZE}
		cxl_vmem_size[$vmem]=${size}
	fi

	# 2 spaces for empty cxl_device.
	if ! [[ "  ${CXL_DEVICES[@]} " =~ " ${cxl_device} " ]]; then
		error "CXL not support device '${cxl_device}', support <${CXL_DEVICES[@]}>"
	fi
}

################################################################################
# Main

TEMP_ARGS=$(getopt --options n:m:k:i:r:d:Q:huDvV \
	--long name: \
	--long cpu: \
	--long memory: \
	--long uefi: \
	--long kernel: \
	--long kcmd: \
	--long initrd: \
	--long rdinit: \
	--long rootfs: \
	--long init: \
	--long root: \
	--long disk: \
	--long nvdimm: \
	--long stdio \
	--long monitor \
	--long cxl: \
	--long virtio-fs-sock: \
	--long virtio-fs-tag: \
	--long dry-run \
	--long qemu: \
	--long qarg: \
	--long gdb \
	--long debug \
	--long verbose \
	--long version \
	--long help \
	--name ${PROG} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-n | --name)
		shift
		q_vm_name=$1
		shift
		;;
	--cpu)
		shift
		handle_cpu_arg ${1}
		shift
		;;
	-m | --memory)
		shift
		q_memory=$(sizeceilfmt $1)
		if [[ -z ${q_memory} ]]; then
			error "Bad memory size parameter $1(${q_memory})"
		fi
		if [[ $(sizechkalign ${q_memory} 256MiB) != y ]]; then
			error "Memory size must align 256MiB"
		fi
		shift
		;;
	--uefi)
		shift
		handle_uefi_arg ${1}
		shift
		;;
	-k | --kernel)
		shift
		f_kernel=$1
		shift
		;;
	--kcmd)
		shift
		kcmds+=( $1 )
		shift
		;;
	-i | --initrd)
		shift
		f_initrd=$1
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
	-d | --disk)
		shift
		handle_disk_arg ${1}
		shift
		;;
	--nvdimm)
		shift
		f_nvdimms+=( $1 )
		shift
		;;
	--cxl)
		shift
		handle_cxl_arg ${1}
		shift
		;;
	--virtio-fs-sock)
		shift
		f_virtiofs_sock+=( $1 )
		shift
		;;
	--virtio-fs-tag)
		shift
		q_virtiofs_tag+=( $1 )
		shift
		;;
	--stdio)
		shift
		q_stdio=ON
		;;
	--monitor)
		shift
		q_monitor=ON
		;;
	-Q | --qemu)
		shift
		QEMU_KVM=$1
		shift
		;;
	--qarg)
		shift
		qargs+=( "${1}" )
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
	-V | --version)
		shift
		echo "${0} ${version}"
		exit 0
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

if [[ ${f_kernel} ]]; then
	check_files_exist_and_exit ${f_kernel}
	[[ -e ${f_kernel} ]] && f_kernel=$(realpath ${f_kernel})
fi

if [[ ${f_initrd} ]]; then
	check_files_exist_and_exit ${f_initrd}
	[[ -e ${f_initrd} ]] && f_initrd=$(realpath ${f_initrd})
fi

if [[ ${f_rootfs} ]]; then
	check_files_exist_and_exit ${f_rootfs}
	check_qemu_format_and_exit ${f_rootfs}
	[[ -e ${f_rootfs} ]] && f_rootfs=$(realpath ${f_rootfs})
fi

check_files_exist_and_exit ${f_virtiofs_sock[@]}

if [[ ! -f ${QEMU_KVM} ]] && [[ -z ${dry_run} ]]; then
	error "Not found qemu ${QEMU_KVM}"
fi

if [[ -z ${f_kernel} ]] && [[ -z ${f_initrd} ]] && [[ -z ${f_disks} ]]; then
	error "must specify kernel and initrd, or specify one disk at least"
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

gen_uuid() {
	if [[ -e /proc/sys/kernel/random/uuid ]]; then
		cat /proc/sys/kernel/random/uuid
	else
		uuid
	fi
}

image2uuid() {
	if [[ ${dry_run} ]]; then
		gen_uuid
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
	qargs+=( -uuid $(gen_uuid) )
	qargs+=( -enable-kvm )
	qargs+=( -boot menu=on )

	# -qmp <protocol>:<path>[,server][,nowait]
	# -qmp unix:/tmp/qmp-sock,server,nowait
	# $ sudo socat - UNIX-CONNECT:/tmp/qmp-sock
	# Or use:
	# -qmp tcp:0.0.0.0:4444,server,nowait
	# $ telnet localhost 4444
	# Or use:
	# -qmp stdio
	qargs+=( -qmp unix:$PWD/qmp-${q_vm_name}.sock,server=on,wait=off )
	cleanup_files+=( $PWD/qmp-${q_vm_name}.sock )

	qargs+=( -pidfile ${q_vm_name}.pid)
	cleanup_files+=( ${q_vm_name}.pid )

	# Qemu monitor
	if [[ ${q_monitor} ]]; then
		# $ telnet localhost PORT
		qargs+=( -monitor tcp:localhost:${q_monitor_telnet_port},server,nowait )

		# Or could use:
		# $ sudo socat - UNIX-CONNECT:/tmp/qemu-monitor-${q_vm_name}.sock
		#qargs+=( -monitor unix:/tmp/qemu-monitor-${q_vm_name}.sock,server,nowait )
		#cleanup_files+=( /tmp/qemu-monitor-${q_vm_name}.sock )
	fi

	if [[ ${q_stdio} ]]; then
		# Default TERM=vt220 if stdio, you could specify
		# TERM=xterm-256color or TERM=linux in your virtual machine.
		qargs+=( -serial mon:stdio )
		qargs+=( -nographic )
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

	# NUMA
	qargs+=( -object memory-backend-memfd,id=mem,size=${q_memory},share=on
			-numa node,memdev=mem )
}

# $1: require memory size
min_memory_required() {
	local reqsz=$1
	if [[ $(size2bytes ${q_memory}) -lt $(size2bytes ${reqsz}) ]]; then
		error "Need memory size ${reqsz} at least, but it's ${q_memory}"
	fi
}

config_cpu() {
	qargs+=( -cpu host )
	qargs+=( -smp cpus=${q_cpus} )
	# TODO: support more cpu
	# qargs+=( -cpu kvm64,+kvm_pv_unhalt,+kvm-pv-ipi,+kvm-pv-tlb-flush )
}

# $1: code
# $2: var, could be empty
__uefi_add_pflash() {
	local code=$1
	local var=$2

	# Other pflash command line:
	#   qargs+=( -drive if=pflash,format=raw,readonly=on,file=${code} )
	#   qargs+=( -drive if=pflash,format=raw,file=${var} )
	qargs+=( -blockdev node-name=pflash0,driver=file,read-only=on,filename=${code} )
	qmachine+=( pflash0=pflash0 )

	if [[ -z ${uefi_novar} ]] && [[ ${var} ]]; then
		qargs+=( -blockdev node-name=pflash1,driver=file,filename=${var} )
		qmachine+=( pflash1=pflash1 )
	fi
}

auto_uefi_pflash() {
	local i code var

	# FIXME: aarch64 default UEFI, skip error:
	# qemu-kvm: device requires 67108864 bytes, block backend provides 786432 bytes
	if [[ ${arch} == aarch64 ]]; then
		return 0
	fi

	for i in ${UEFI_CODES[@]}; do
		if [[ -e ${i} ]]; then
			code=${i}
			break
		fi
	done

	for i in ${UEFI_VARS[@]}; do
		if [[ ! -e ${i} ]]; then
			continue
		fi

		# Copy a new VAR from system OS.
		var=${i}
		local newvar=${q_vm_name}_$(basename ${var})
		cp ${var} ${newvar}
		cleanup_files+=( ${newvar} )
		var=${newvar}
		break
	done

	if [[ -z ${code} ]] && [[ -z ${dry_run} ]]; then
		error "not found uefi code: ${UEFI_CODES[@]}"
	fi

	__uefi_add_pflash ${code} ${var}
}

set_uefi_pflash() {
	if [[ ${uefi_code} ]]; then
		__uefi_add_pflash ${uefi_code} ${uefi_var}
	else
		auto_uefi_pflash
	fi
}

config_uefi() {
	set_uefi_pflash
}

config_pci() {
	local i args

	# Config pcie-root-port
	for i in $(seq 1 ${pcie_root_port_num}); do
		unset args
		args+=( bus=${BUS_PCIE0} )
		args+=( id=pcie.${i} )
		args+=( chassis=${i} )
		args+=( port=${i} )
		qargs+=( -device pcie-root-port,$(IFS=,; echo "${args[*]}") )
	done
}

add_net_nic_user() {
	qargs+=(-netdev type=user,id=net0
		-device virtio-net-pci,bus=${BUS_PCIE0},netdev=net0,addr=6.0 )
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
	qargs+=( -net user,hostfwd=tcp::8086-:22 )
	qargs+=( -net nic,model=virtio
		-device virtio-net,netdev=network0
		-netdev tap,id=network0,ifname=tap0,script=no,downscript=no )
}

config_net() {
	add_net_nic_user_tap
}

config_kernel() {
	[[ ${f_kernel} ]] && qargs+=( -kernel ${f_kernel} )
	[[ ${f_initrd} ]] && qargs+=( -initrd ${f_initrd} )

	if [[ -z ${f_kernel} ]]; then
		return 0
	fi

	if [[ ${debug} ]]; then
		kcmds+=( rd.debug )
		kcmds+=( systemd.log_level=debug )
	fi

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
	if [[ -z ${f_rootfs} ]]; then
		# if not rootfs, we should break in initrd.
		kcmds+=( rd.break ) # dracut.cmdline(7)
		return 0
	else
		kcmds+=( ${k_rw} )

		if [[ ${k_root} ]]; then
			kcmds+=( root=${k_root} )
		else
			kcmds+=( root=UUID=$(image2uuid ${f_rootfs}) )
		fi
	fi

	if [[ -z "${cxl_device}${cxl_pxb_ids}" ]]; then
		if [[ ${debug} ]]; then
			kcmds+=( "cxl_acpi.dyndbg=+fplm"
				"cxl_pci.dyndbg=+fplm"
				"cxl_core.dyndbg=+fplm"
				"cxl_mem.dyndbg=+fplm"
				"cxl_pmem.dyndbg=+fplm"
				"cxl_port.dyndbg=+fplm"
				"cxl_region.dyndbg=+fplm"
				"cxl_test.dyndbg=+fplm"
				"cxl_mock.dyndbg=+fplm"
				"cxl_mock_mem.dyndbg=+fplm" )
		fi
		# Disable ACPI CXL enumeration at boot
		# kcmds+=( acpi=off )
		kcmds+=( cxl.mem=disable )
		kcmds+=( cxl.acpi=0 )
	fi
}

__disk_file_type() {
	local file=$1
	local ft=$(ftype ${file})
	if [[ -z ${ft} ]] && [[ ${dry_run} ]]; then
		ft=${file##*.}
	fi
	if [[ -z ${ft} ]]; then
		ft=raw
		warning "Treat ${file} as ${ft}"
	fi
	echo ${ft}
}

add_virtio_disk() {
	local f_img=$1
	local f_type=$(__disk_file_type ${f_img})
	local virtio_id=$(mktemp -u virtio-XXXXXX)
	qargs+=( -drive file=${f_img},format=${f_type},if=none,id=${virtio_id}
		-device virtio-blk,drive=${virtio_id} )
}
add_sata_disk() {
	local f_img=$1
	local f_type=$(__disk_file_type ${f_img})
	local sata_id=$(mktemp -u sata-XXXXXX)
	qargs+=( -device ahci,id=ahci0
		-drive if=none,file=${f_img},format=${f_type},id=${sata_id}
		-device ide-hd,bus=ahci0.0,drive=${sata_id} )
}
add_nvme_disk() {
	local f_img=$1
	local f_type=$(__disk_file_type ${f_img})
	local drive_id=$(mktemp -u nvme-XXXXXX)
	qargs+=( -drive if=none,file=${f_img},format=${f_type},id=${drive_id}
		-device nvme,drive=${drive_id},serial=sn-${drive_id} )
}

add_scsi_disk() {
	local f_img=$1
	local f_type=$(__disk_file_type ${f_img})
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
		return 0
	fi

	case ${f_rootfs_type} in
	${DISK_VIRTIO}) add_virtio_disk ${f_rootfs} ;;
	${DISK_SATA}) add_sata_disk ${f_rootfs} ;;
	${DISK_NVME}) add_nvme_disk ${f_rootfs} ;;
	${DISK_SCSI}) add_scsi_disk ${f_rootfs} ;;
	${DISK_NVDIMM}) add_nvdimm_blk ${f_rootfs} ;;
	esac
}

config_disk() {
	if [[ -z ${f_disks} ]]; then
		return 0
	fi

	local disk
	for disk in ${f_disks[@]}
	do
		#qargs+=( -drive file=$(realpath ${disk}),format=raw )
		add_virtio_disk ${disk}
	done
}

config_nvdimm() {
	local nvdimm
	for nvdimm in ${f_nvdimms[@]}
	do
		check_files_exist_and_exit ${nvdimm}
		add_nvdimm_blk $(realpath ${nvdimm})
	done
}

next_pxb_cxl_id() {
	echo $(mktemp -u cxl.pxb.XXXX)
}

# bus_nr=11,21,31,41,...
__pxb_cxl_bus_nr_file=$(mktemp -u)
cleanup_files+=( ${__pxb_cxl_bus_nr_file} )
next_cxl_pxb_bus_nr() {
	local num=11
	if [[ -f ${__pxb_cxl_bus_nr_file} ]]; then
		num=$(cat ${__pxb_cxl_bus_nr_file})
	fi
	echo "${num}"
	echo $((num + 10)) > ${__pxb_cxl_bus_nr_file}
}

next_cxl_rp_id() {
	echo $(mktemp -u cxl.rp.XXXX)
}

__cxl_slot_file=$(mktemp -u)
cleanup_files+=( ${__cxl_slot_file} )
next_cxl_slot() {
	local num=1
	if [[ -f ${__cxl_slot_file} ]]; then
		num=$(cat ${__cxl_slot_file})
	fi
	echo "${num}"
	echo $((++num)) > ${__cxl_slot_file}
}

next_cxl_type3_id() {
	echo $(mktemp -u cxl.type3.XXXX)
}

next_cxl_vmem_id() {
	echo $(mktemp -u cxl.vmem.XXXX)
}

next_cxl_pmem_id() {
	echo $(mktemp -u cxl.pmem.XXXX)
}

next_cxl_switch_upstream_id() {
	echo $(mktemp -u cxl.switch.upstream.XXXX)
}

# $1: 0 1 2 3
add_cxl_fmw() {
	if ! [[ " ${cxl_fmw[@]} " =~ " $1 " ]]; then
		cxl_fmw+=( $1 )
	fi
	return 0
}

# cxl pcie eXpander bridge
# $1: specify pxb id, could use next_pxb_cxl_id() get a random id
# $2: specify fmw id, default is 0
add_cxl_pxb() {
	local id=$1
	local fmw=${2-0}
	local arg

	arg+=( pxb-cxl )
	arg+=( id=${id} )
	arg+=( bus=${BUS_PCIE0} )
	arg+=( bus_nr=$(next_cxl_pxb_bus_nr) )

	qargs+=( -device $(IFS=,; echo "${arg[*]}") )

	# add to global list, maybe use to -machine
	if ! [[ " ${cxl_pxb_ids[@]} " =~ " ${id} " ]]; then
		cxl_pxb_ids+=( ${id} )
	fi

	# set cxl fmw for pxb
	if [[ ${cxl_pxb_fmw[$id]} ]] && [[ ${cxl_pxb_fmw[$id]} != ${fmw} ]]; then
		error "cxl: try to set different fmw for pxb ${id} (old ${cxl_pxb_fmw[$id]}, new ${fmw})"
	fi
	[[ -z ${cxl_pxb_fmw[$id]} ]] && cxl_pxb_fmw[$id]=${fmw}
	add_cxl_fmw ${fmw}

	return 0
}

# root port
# $1: bus (cxl pxb id)
# $2: id, root port id, maybe generated by next_cxl_rp_id()
# $3: port
add_cxl_rp() {
	local bus=$1
	local id=$2
	local port=$3
	local arg

	arg+=( cxl-rp )
	arg+=( port=${port} )
	arg+=( bus=${bus} )
	arg+=( id=${id} )
	arg+=( chassis=0 )
	arg+=( slot=$(next_cxl_slot) )

	if ! [[ " ${cxl_pxb_ids[@]} " =~ " ${bus} " ]]; then
		error "cxl root port can't use a non-exist bus pxb"
	fi

	if ! [[ " ${cxl_rp_ids[@]} " =~ " ${id} " ]]; then
		cxl_rp_ids+=( ${id} )
	fi

	# Each root port belongs to one single pxb, and pxb has many root port.
	cxl_pxb2rps[${bus}]+=" ${id}"
	[[ ${cxl_rp2pxb[${id}]} ]] && \
		error "cxl rp ${id} already has pxb ${cxl_rp2pxb[${id}]}"
	cxl_rp2pxb[${id}]="${bus}"

	qargs+=( -device $(IFS=,; echo "${arg[*]}") )
}

# cxl switch
#
#              UP    upstream
# ┌───────────┬─┬───────────┐
# │CXL Switch └─┘           │
# │ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ │
# └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
#    D1  D2  D3  D4  D5  D6
#                  downstream
#
# --bus=<name>: set bus
# --nport=<num>: set number of downstream ports
# --port-prefix=<prefix>: prefix name of port id, the <nport> will append to it.
#                         ${prefix}.${1 ~ nport}
add_cxl_switch() {
	local i
	local bus nport portprefix
	local dsarg # downstream arguments

	local TEMP=$(getopt \
		--options B: \
		--long bus: \
		--long nport: \
		--long port-prefix: \
		-n $0 -- "$@")

	test $? != 0 && error "$0 parse arguments failed, ${@}"

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-B | --bus)
			shift
			bus=$1
			shift
			;;
		--nport)
			shift
			nport=$1
			shift
			;;
		--port-prefix)
			shift
			portprefix=$1
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	local up_id=$(next_cxl_switch_upstream_id)

	qargs+=( -device cxl-upstream,bus=${bus},id=${up_id} )

	# switch upstream has a root port
	cxl_switch_up2rp[${up_id}]="${bus}"

	if [[ "${cxl_rp2swup[${bus}]}" ]]; then
		error "cxl rootport ${bus} already has switch upstream ${cxl_rp2swup[${bus}]}"
	fi
	cxl_rp2swup[${bus}]="${up_id}"

	for i in $(seq 1 1 ${nport})
	do
		local down_id="${portprefix}.${i}"

		dsarg+=( cxl-downstream )
		dsarg+=( port=${i} )
		dsarg+=( bus=${up_id} )
		dsarg+=( id=${down_id} )
		dsarg+=( chassis=0 )
		dsarg+=( slot=$(next_cxl_slot) )

		# Each cxl switch downstream has a upstream, on upstream has
		# not only one downstream.
		cxl_switch_down2up[${down_id}]="${up_id}"
		cxl_switch_up2downs[${up_id}]+=" ${down_id}"

		qargs+=( -device $(IFS=,; echo "${dsarg[*]}") )
		unset dsarg
	done
}

# cxl type3 device
# --pmem <name>: set pmem name
# --vmem <name>: set vmem name
# --bus <name>: set bus
# --lsa <name>: set lsa, skip if SKIP
add_cxl_type3_dev() {
	local arg tmparg
	local pmem vmem name
	local bus lsa
	local size

	local TEMP=$(getopt \
		--options t: \
		--long pmem: \
		--long vmem: \
		--long bus: \
		--long lsa: \
		--long size: \
		-n $0 -- "$@")

	test $? != 0 && error "$0 parse arguments failed, ${@}"

	eval set -- "$TEMP"

	while true; do
		case $1 in
		--pmem)
			shift
			pmem=$1
			shift
			;;
		--vmem)
			shift
			vmem=$1
			shift
			;;
		--bus)
			shift
			bus=$1
			shift
			;;
		--lsa)
			shift
			lsa=$1
			shift
			;;
		--size)
			shift
			size=$1
			size=$(sizeceilfmt ${size})
			if [[ -z ${size} ]]; then
				error "Bad cxl type3 memory size parameter: ${1}"
			fi
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	if [[ -z ${size} ]]; then
		size=${CXL_DEFAULT_MSIZE}
	fi

	if [[ ${pmem} ]] && [[ ${vmem} ]]; then
		error "cxl-type3 not allow pmem and vmem at the same time"
	fi

	if [[ -z ${pmem} ]] && [[ -z ${vmem} ]]; then
		error "cxl-type3 must specify one of pmem vmem"
	fi

	[[ -z ${bus} ]] && error "cxl-type3 need bus="

	arg+=( cxl-type3 )
	arg+=( bus=${bus} )

	if [[ ${pmem} ]]; then
		# persistent memory size cxl_pmem_size[] set in arguments first,
		# if use CXL_DEVICES[], cxl_pmem_size[] will be empty, so, we
		# just set it here.
		if [[ -z ${lsa} ]] || [[ ${lsa} == SKIP ]]; then
			error "lsa property must be set for persistent devices"
		fi

		if [[ ! -z ${cxl_pmem_size[$pmem]} ]]; then
			if [[ $(sizeceilfmt ${size}) != $(sizeceilfmt ${cxl_pmem_size[$pmem]}) ]]; then
				error "pmem set different size ${size} and ${cxl_pmem_size[$pmem]}"
			fi
		else
			cxl_pmem_size[$pmem]=${size}
		fi

		arg+=( persistent-memdev=${pmem} )

		local pmem_file=${PWD}/${pmem}.raw
		_eval qemu-img create -f raw ${pmem_file} ${size}
		cleanup_files+=( ${pmem_file} )

		name=${pmem}

		tmparg+=( memory-backend-file )
		tmparg+=( id=${pmem} )
		tmparg+=( share=on )
		tmparg+=( mem-path=${pmem_file} )
		tmparg+=( size=${size} )
		qargs+=( -object $(IFS=,; echo "${tmparg[*]}") )
		unset tmparg
	fi

	if [[ ${vmem} ]]; then
		# volatile memory size cxl_vmem_size[] set in arguments first,
		# if use CXL_DEVICES[], cxl_vmem_size[] will be empty, so, we
		# just set it here.
		if [[ ! -z ${cxl_vmem_size[$vmem]} ]]; then
			if [[ $(sizeceilfmt ${size}) != $(sizeceilfmt ${cxl_vmem_size[$vmem]}) ]]; then
				error "vmem set different size ${size} and ${cxl_vmem_size[$vmem]}"
			fi
		else
			cxl_vmem_size[$vmem]=${size}
		fi

		name=${vmem}
		qargs+=( -object memory-backend-ram,id=${vmem},share=on,size=${size} )
		arg+=( volatile-memdev=${vmem} )
	fi

	if [[ ${lsa} ]] && [[ ${lsa} != SKIP ]]; then
		arg+=( lsa=${lsa} )

		local lsa_file=${PWD}/${lsa}.raw
		_eval qemu-img create -f raw ${lsa_file} ${size}
		cleanup_files+=( ${lsa_file} )

		tmparg+=( memory-backend-file,id=${lsa} )
		tmparg+=( share=on )
		tmparg+=( mem-path=${lsa_file} )
		tmparg+=( size=${size} )
		qargs+=( -object $(IFS=,; echo "${tmparg[*]}") )
		unset tmparg
	fi

	local type3_id=$(next_cxl_type3_id)

	# cxl type3 device belongs to a rootport or a switch
	cxl_pvmem_id2bus[${type3_id}]="${bus}"
	cxl_pvmem_id2name[${type3_id}]="${name}"
	cxl_pvmem_ids+=( ${type3_id} )

	# This cxl type2 device bus is root port
	if [[ " ${cxl_rp_ids[@]} " =~ " ${bus} " ]]; then
		if [[ "${cxl_rp2pvmem[$bus]}" ]]; then
			error "cxl rootport ${bus} already have device ${cxl_rp2pvmem[$bus]}"
		fi
		cxl_rp2pvmem[${bus}]=${type3_id}
	# This cxl type2 device bus is cxl switch downstream
	elif [[ ${cxl_switch_down2up[$bus]} ]]; then
		if [[ "${cxl_switch_down2pvmem[$bus]}" ]]; then
			error "cxl switch downstream already have device ${cxl_switch_down2pvmem[$bus]}"
		fi
		cxl_switch_down2pvmem[${bus}]+=" ${type3_id}"
	else
		error "add cxl type3 device to non exist rootport or switch"
	fi

	arg+=( id=${type3_id} )
	# Hope it will not conflict
	arg+=( sn=$RANDOM )

	qargs+=( -device $(IFS=,; echo "${arg[*]}") )
}

# A setup suitable for multi ways interleave. Only one fixed window provided, to
# enable multi ways interleave across 2 CXL host bridges. Each host bridge has 2
# CXL Root Ports, with the CXL Type3 device directly attached (no switches).
__cxl_pmem_ways() {
	local i ways=${1}

	# TODO: Why cxl pmem 4way need higher ram memory than CXL Type3?
	min_memory_required $((${ways} + 1))G

	local pxb_id1=$(next_pxb_cxl_id)

	add_cxl_pxb ${pxb_id1}

	for ((i = 1; i <= ${ways}; i++))
	do
		local tmparg
		local rp_id=$(next_cxl_rp_id)

		add_cxl_rp ${pxb_id1} ${rp_id} ${i}

		# Or could add it to CXL switch
		add_cxl_type3_dev --pmem=$(next_cxl_pmem_id) --bus=${rp_id} --lsa=cxl-lsa${i}
	done
}

cxl_pmem() {
	__cxl_pmem_ways 1
}

cxl_pmem_4way() {
	__cxl_pmem_ways 4
}

# An example of 4 devices below a switch suitable for 1, 2 or 4 way interleave:
cxl_pmem_4way_switch() {
	local pxb_id=$(next_pxb_cxl_id)
	local rp_id1=$(next_cxl_rp_id)
	local rp_id2=$(next_cxl_rp_id)

	add_cxl_pxb ${pxb_id}

	add_cxl_rp ${pxb_id} ${rp_id1} 0
	add_cxl_rp ${pxb_id} ${rp_id2} 1

	add_cxl_switch --bus=${rp_id1} --nport=4 --port-prefix=swport

	for i in $(seq 1 1 4)
	do
		add_cxl_type3_dev --pmem=$(next_cxl_pmem_id) --bus=swport.${i} --lsa=cxl-lsa${i}
	done
}

__cxl_volatile_mem_lsa() {
	local ways=${1}
	local lsa=${2}
	local LSA

	if [[ ${lsa} == lsa ]]; then
		LSA="--lsa=cxl-lsa0"
	fi

	local pxb_id=$(next_pxb_cxl_id)

	add_cxl_pxb ${pxb_id}

	for i in $(seq 1 1 ${ways})
	do
		local rp_id=$(next_cxl_rp_id)

		add_cxl_rp ${pxb_id} ${rp_id} ${i}

		add_cxl_type3_dev --vmem=$(next_cxl_vmem_id) --bus=${rp_id} ${LSA}
	done
}

cxl_volatile_mem() {
	__cxl_volatile_mem_lsa 1
}

cxl_volatile_mem_lsa() {
	__cxl_volatile_mem_lsa 1 lsa
}

cxl_volatile_mem_4way() {
	__cxl_volatile_mem_lsa 4
}

cxl_volatile_mem_4way_switch() {
	local pxb_id=$(next_pxb_cxl_id)
	local rp_id1=$(next_cxl_rp_id)
	local rp_id2=$(next_cxl_rp_id)

	add_cxl_pxb ${pxb_id}

	add_cxl_rp ${pxb_id} ${rp_id1} 0
	add_cxl_rp ${pxb_id} ${rp_id2} 1

	add_cxl_switch --bus=${rp_id1} --nport=4 --port-prefix swport

	for i in $(seq 1 1 4)
	do
		add_cxl_type3_dev --vmem=$(next_cxl_vmem_id) --bus=swport.${i}
	done
}

pcxltopo() {
	if [[ -z ${cxl_show_topology} ]]; then
		return
	fi
	printf "${@}"
}

cxl_topolopy() {
	local pxb rp swup swdown pvmem

	pcxltopo "cxl_pxb_ids: [${cxl_pxb_ids[*]}]\n"
	for pxb in ${cxl_pxb_ids[@]}
	do
		pcxltopo "cxl_pxb_fmw[$pxb]: ${cxl_pxb_fmw[$pxb]}\n"
		pcxltopo "cxl_pxb2rps[${pxb}]: ${cxl_pxb2rps[$pxb]}\n"
		for rp in ${cxl_pxb2rps[$pxb]}
		do
			if [[ "${cxl_rp2swup[$rp]}" ]]; then
				pcxltopo "cxl_rp2swup[$rp]: ${cxl_rp2swup[$rp]}\n"
				for swup in ${cxl_rp2swup[$rp]}
				do
					pcxltopo "cxl_switch_up2downs[$swup]: ${cxl_switch_up2downs[$swup]}\n"
					for swdown in ${cxl_switch_up2downs[$swup]}
					do
						pcxltopo "cxl_switch_down2pvmem[$swdown] = ${cxl_switch_down2pvmem[$swdown]}\n"
					done
				done
			elif [[ "${cxl_rp2pvmem[$rp]}" ]]; then
				pcxltopo "cxl_rp2pvmem[$rp]: ${cxl_rp2pvmem[$rp]}\n"
			fi
		done
	done

	for mem_id in ${cxl_pvmem_ids[@]}
	do
		local bus=${cxl_pvmem_id2bus[$mem_id]}
		local memname=${cxl_pvmem_id2name[$mem_id]}
		[[ -z ${bus} ]] && error "not found bus of cxl device ${mem_id}"
		[[ -z ${memname} ]] && error "not found name of cxl device ${mem_id}"

		local pmemsz=${cxl_pmem_size[$memname]}
		local vmemsz=${cxl_vmem_size[$memname]}
		local memsz=0
		if [[ -z ${pmemsz} ]] && [[ -z ${vmemsz} ]]; then
			error "not found size of cxl type3 device"
		fi
		if [[ ${pmemsz} ]] && [[ ${vmemsz} ]]; then
			error "cxl type3 device ${memname} mistake, pmem or vmem?"
		fi
		[[ ${pmemsz} ]] && memsz=${pmemsz}
		[[ ${vmemsz} ]] && memsz=${vmemsz}

		pcxltopo "${mem_id}(${memname},size=${memsz})->"

		swdown=${bus}
		swup=${cxl_switch_down2up[$swdown]}

		if [[ ${swup} ]]; then
			pcxltopo "${swdown}->${swup}->"
			rp=${cxl_switch_up2rp[$swup]}
		else
			rp=${bus}
		fi

		[[ -z ${rp} ]] && error "not found rp"
		pcxltopo "${rp}->"

		pxb=${cxl_rp2pxb[$rp]}
		[[ -z ${pxb} ]] && error "not found pxb"

		# update pxb size
		memsz=$(size2bytes ${memsz})
		local prevsz=$(size2bytes ${cxl_pxb_sizes[$pxb]})
		prevsz=$(sizeceilfmt $(( prevsz + memsz )))
		cxl_pxb_sizes[$pxb]=${prevsz}

		pcxltopo "${pxb}(fmw=${cxl_pxb_fmw[$pxb]})->${BUS_PCIE0}\n"
	done

	for pxb in ${!cxl_pxb_sizes[@]}
	do
		pcxltopo "pxb ${pxb} total size ${cxl_pxb_sizes[$pxb]}\n"
	done
}

config_cxl() {
	local i j k

	if [[ -z "${cxl_device}${cxl_pxb_ids}" ]]; then
		return 0
	fi

	qmachine+=( cxl=on )
	qmachine+=( nvdimm=on )

	# Create CXL PXB
	for i in ${cxl_pxb_ids[@]}
	do
		add_cxl_pxb ${i} ${cxl_pxb_fmw[$i]}
	done

	# Create CXL RootPort
	for ((i = 0; i < ${#cxl_rp_ids[@]}; i++))
	do
		add_cxl_rp ${cxl_rp_buss[i]} ${cxl_rp_ids[i]} \
			   ${cxl_rp_ports[i]}
	done

	for ((i = 0; i < ${#cxl_switches_ndport[@]}; i++))
	do
		add_cxl_switch --bus=${cxl_switches_bus[i]} \
			--nport=${cxl_switches_ndport[i]} \
			--port-prefix=${cxl_switches_dportpfx[i]}
	done

	for ((i = 0; i < ${#cxl_pmem_names[@]}; i++))
	do
		local pmem=${cxl_pmem_names[i]}
		add_cxl_type3_dev --pmem=${pmem} \
			--bus=${cxl_pmem_bus[$pmem]} \
			--lsa=${cxl_pmem_lsa[$pmem]} \
			--size=${cxl_pmem_size[$pmem]}
	done

	for ((i = 0; i < ${#cxl_vmem_names[@]}; i++))
	do
		local vmem=${cxl_vmem_names[i]}
		add_cxl_type3_dev --vmem=${vmem} \
			--bus=${cxl_vmem_bus[$vmem]} \
			--lsa=${cxl_vmem_lsa[$vmem]} \
			--size=${cxl_vmem_size[$vmem]}
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
	${CXL_DEV_VMEM})
		cxl_volatile_mem
		;;
	${CXL_DEV_VMEM_LSA})
		cxl_volatile_mem_lsa
		;;
	${CXL_DEV_VMEM_4WAY})
		cxl_volatile_mem_4way
		;;
	${CXL_DEV_VMEM_4WAY_SWITCH})
		cxl_volatile_mem_4way_switch
		;;
	esac

	cxl_topolopy

	# Config CFMW (CXL Fixed Memory Window)
	for j in ${cxl_fmw[@]}
	do
		local fmwsz=0

		for ((i = 0, k = 0; i < ${#cxl_pxb_ids[@]}; i++))
		do
			local pxb_id=${cxl_pxb_ids[i]}
			if [[ ${cxl_pxb_fmw[$pxb_id]} == ${j} ]]; then
				qmachine+=( cxl-fmw.${j}.targets.${k}=${pxb_id} )
				k=$(expr $k + 1)
				# calulate fmw size
				fmwsz=$(sizesum ${fmwsz} ${cxl_pxb_sizes[$pxb_id]})
			fi
		done

		# align 256MiB
		fmwsz=$(sizeceilfmt ${fmwsz})
		[[ -z ${fmwsz} ]] && error "cxl: failed to get pxb size sum"
		qmachine+=( cxl-fmw.${j}.size=${fmwsz} )

		# 256, 512, 1k, 2k, 4k, 8k, 16k, default 256
		qmachine+=( cxl-fmw.${j}.interleave-granularity=4k )
	done
}

config_virtiofs() {
	if [[ -z ${f_virtiofs_sock} ]] && [[ -z ${q_virtiofs_tag} ]]; then
		return
	fi

	if [[ -z ${f_virtiofs_sock} ]] || [[ -z ${q_virtiofs_tag} ]]; then
		error "Must specify --virtio-fs-sock and --virtio-fs-tag at the same time"
	fi

	if [[ ${#f_virtiofs_sock[@]} -ne ${#q_virtiofs_tag[@]} ]]; then
		error "Number of --virtio-fs-sock must equal to --virtio-fs-tag"
	fi

	# ref: https://qemu-stsquad.readthedocs.io/en/doc-updates/tools/virtiofsd.html
	local i
	for ((i = 0; i < ${#f_virtiofs_sock[@]}; i++))
	do
		qargs+=( -chardev socket,id=char${i},path=${f_virtiofs_sock[i]}
			-device vhost-user-fs-pci,chardev=char${i},bus=${BUS_PCIE0},tag=${q_virtiofs_tag[i]} )
	done
}

config_basic
config_memory
config_cpu
config_uefi
config_pci
config_net
config_kernel
config_rootfs
config_disk
config_nvdimm
config_cxl
config_virtiofs

qmachine=( $(printf "%s\n" ${qmachine[@]} | sort -u) )
qargs+=( -machine $(IFS=,; echo "${qmachine[*]}") )

_eval ${QEMU_KVM} ${qargs[@]} ${kcmds:+-append \"${kcmds[@]}\"}
