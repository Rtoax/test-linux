#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
#
# Use the qemu command to create a virtual machine directly, without using
# libvirt, but directly use the qemu command line parameters.
#
set -e

readonly PROG=qemu-vm
readonly ARCH=$(uname -m)
readonly VERSION="v1.1.16"
readonly QEMU_VM_ROOT=$(dirname $(realpath $0))

declare QEMU QEMU_VERSION QEMU_MAJOR QEMU_MINOR QEMU_PATCH

# on x86_64: 'q35' default root bus
readonly BUS_PCIE0=pcie.0
declare pcie_root_port_num=2

declare q_vm_name=$(mktemp -u vm-XXXXXX)
declare q_cpus=4
declare q_cpu_model=host
declare q_memory=2G

declare f_kernel
declare f_initrd
declare k_rdinit

declare f_rootfs
declare f_rootfs_type
declare k_init
declare k_root
# root mount attr: 'ro', 'rw'. default: 'rw'
declare k_rw

declare -a f_nvdimms

# Disk shoud contains boot(EFI) partition, kernel, initramfs, etc.
declare -a f_disks

declare -a f_virtiofs_sock
declare -a q_virtiofs_tag

declare q_stdio
declare q_daemon
declare q_gdb

declare dry_run
declare verbose
declare debug
declare TMPDIR=/tmp/${PROG}

# Store VM specific files on host filesystem
declare vm_tmpdir
declare vm_cmd_sh
declare vm_port_hostfwd_ssh22
declare vm_port_monitor_telnet

# Port
declare TCP_PORT_HOSTFWM_SSH22
declare TCP_PORT_MONITOR_TELNET

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
declare have_cxl

readonly FORMAT_SIZE="${UL}SIZE${RST}: B, K, KB, KiB, M, MB, MiB, G, GB, GiB"

. ${QEMU_VM_ROOT}/libcpu.sh
. ${QEMU_VM_ROOT}/libfile.sh
. ${QEMU_VM_ROOT}/liblog.sh
. ${QEMU_VM_ROOT}/libnbd.sh
. ${QEMU_VM_ROOT}/librun.sh
. ${QEMU_VM_ROOT}/libnet.sh
. ${QEMU_VM_ROOT}/libuuid.sh
. ${QEMU_VM_ROOT}/libqemu.sh
. ${QEMU_VM_ROOT}/libqemu-cxl.sh
. ${QEMU_VM_ROOT}/libstring.sh

qemu_eval()
{
	DRY_RUN_LOG=${vm_cmd_sh} DRY_RUN=${dry_run} dry_run "${@}"
}

__usage_internal__() {
	echo -e "
${BOLD}NAME${RST}
    ${PROG} - Running a virtual machine with Qemu-KVM

${BOLD}SYNOPSIS${RST}
    ${PROG} ${GRAY}[subcmd]${RST} -k=<kernel> -i=<initrd> [-r=<rootfs>] [-m=4G] [--stdio]

${BOLD}DESCRIPTION${RST}
    Running a virtual machine with Qemu-KVM, support flexable arguments.

    Virtual machine monitor, port see ${UL}${PROG} list --port${RST}, connect with
    ${GRAY}$ telnet localhost PORT${RST} or ${GRAY}$ nc localhost PORT${RST} for qemu monitor,
    connect guest ssh with ${GRAY}$ ssh -p PORT USER:localhost${RST}.

${BOLD}SUBCOMMAND OPTIONS${RST}
    list                    listing all current running VMs
    destroy [NAME]          destroy a virtual machine

${BOLD}VM OPTIONS${RST}
    -n, --name [NAME]       specify vm name, default: vm- prefix

    --cpu [ARGS]            config CPU, please see ${BOLD}--cpu help${RST}
    -m, --memory [SIZE]     Sets guest startup RAM size, default: ${q_memory},
                            format see ${UL}SIZE${RST} section.

    -k, --kernel [KERNEL]   specify ${UL}vmlinux${RST}, ${UL}vmlinuz${RST}, ${UL}bzImage${RST}
        --kcmd [ARG]        add kernel cmdline (may be listed multiple times)
                            example: --kcmd=${GRAY}rdinit=/usr/bin/bash${RST}

    -i, --initrd [INITRD]   specify initrd image.
                            If you use ${UL}dracut${RST} generate initrd, and you
                            pass the rootfs, you must add ${UL}--no-host-only${RST} argument,
                            otherwise, ${UL}/dev/disk/by-xxx${RST} may not be found.

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
    -Q, --qemu [qemu-kvm]   specify qemu emulator binary,
                            default: ${UL}${QEMU}${RST}, version ${UL}${QEMU_VERSION}${RST}

        --gdb               enable qemu debugging, usage:${GRAY}
                            $ gdb -q kernel.elf
                            (gdb) target remote :1234
                            (gdb) hbreak start_kernel
                            (gdb) continue${RST}
                            the ${UL}kernel.elf${RST} also could get:${GRAY}
                            $ objcopy --only-keep-debug vmlinux kernel.elf${RST}

    --qarg [ARG]            append ARG to qemu arguments,
                            (may be listed multiple times)
                            for example:
                            if want to pass ${BOLD}-fw_cfg${RST} to qemu:
                              ${GRAY}-fw_cfg [name=]<name>,file=<file>${RST}
                              ${GRAY}-fw_cfg [name=]<name>,[name=]<name>,string=<str>${RST}
                            you could:
                              ${GRAY}$ ${PROG} --qarg \"-fw_cfg name=${USER},file=/etc/os-release\"${RST}
                            in guestos, check ${BOLD}/sys/firmware/qemu_fw_cfg/${RST}

  ${BOLD}CXL OPTIONS${RST}
    --cxl [ARGS]            CXL by Qemu. please see ${BOLD}--cxl help|?${RST}
                            (may be listed multiple times)

                            CXL require Qemu >= ${UL}9.0${RST} on aarch64,
                            Qemu >= ${UL}7.2${RST} on x86_64.

  ${BOLD}COMMON OPTIONS${RST}
    -u, --dry-run           only show commands
    -D, --debug             enable debug mode.
    -v, --verbose           enable verbose mode.
    -V, --version           show version
    -h, --help              show this help information"

	local kernel="${GRAY}${ITALIC}/boot/vmlinuz-$(uname -r)${RST}"
	local initrd="${GRAY}${ITALIC}/boot/initramfs-$(uname -r).img${RST}"

	echo -e "
${BOLD}EXAMPLES${RST}
    $ sudo ${PROG} --kernel ${kernel} \\
        --initrd ${initrd} ${GRAY}[--rdinit=/bin/bash]${RST} \\
        ${GRAY}[--rootfs vm.raw] [--init=/usr/bin/bash]${RST} --stdio"

	echo -e "
${BOLD}MINIMAL QEMU COMMANDS${RST}"

	case ${ARCH} in
	x86_64)
		echo -e "
    ${GRAY}# On x86_64${RST}
    $ sudo ${QEMU} -machine q35 -cpu host -accel kvm -m 2G \\
        -kernel ${kernel} -initrd ${initrd} \\
        -append \"console=ttyS0,115200 rdinit=/bin/bash rw\" \\
        -nographic ${q_gdb:+-s -S}"
		;;
	aarch64)
		echo -e "
    ${GRAY}# On aarch64${RST}
    $ sudo ${QEMU} -machine virt -cpu host -accel kvm -m 2G \\
        -kernel ${kernel} -initrd ${initrd} \\
        -append \"earlycon console=ttyAMA0 rdinit=/bin/bash rw\" \\
	-nographic ${q_gdb:+-s -S}"
		;;
	esac
	echo -e "
${BOLD}FORMAT${RST}

  ${FORMAT_SIZE}

${BOLD}SEE ALSO${RST}
    qemu(1), qemu-kvm(1), etc.

${BOLD}AUTHOR${RST}
    Written by Rong Tao.
"
}

__usage__() {
	__usage_internal__ "${@}" | more
	exit ${1-0}
}

# $1: qemu-kvm emulator
set_qemu_kvm() {
	QEMU=${1}

	if [[ ! -f ${QEMU} ]] &&
	   [[ -z "$(which ${QEMU})" ]] &&
	   [[ -z ${dry_run} ]]; then
		error "Not found qemu ${QEMU}"
	fi

	QEMU_VERSION="$(${QEMU} --version | \
		grep -m1 -Ewo '[0-9]+\.[0-9]+\.[0-9]+' | head -1)"
	QEMU_MAJOR="$(echo ${QEMU_VERSION} | awk -F '.' '{print $1}')"
	QEMU_MINOR="$(echo ${QEMU_VERSION} | awk -F '.' '{print $2}')"
	QEMU_PATCH="$(echo ${QEMU_VERSION} | awk -F '.' '{print $3}')"
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
${BOLD}--cpu model=[MODEL]${RST}: set cpu model (default: ${UL}${q_cpu_model}${RST}), see ${GRAY}${QEMU} -cpu help${RST}
"
	exit 0
}

handle_cpu_arg() {
	local arg args
	local nr_cpus model

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

	if [[ ${#args[@]} -eq 1 ]] &&
	   [[ $(echo ${1} | tr '=,' ' ' | wc -w) -eq 1 ]]; then
		# Avoid extra non-digest char, like '--cpu 16,'
		if ! [[ ${1} =~ ^[0-9]+$ ]]; then
			error "cpu: unknown '${1}', see --cpu help"
		fi
	fi

	unset args

	if [[ $(echo $1 | tr '=,' ' ' | wc -w) -gt 1 ]]; then
		args=( $(echo $1 | tr ',' ' ') )
		for arg in ${args[@]}
		do
			case ${arg%%=*} in
			nr)
				nr_cpus=${arg:3}
				;;
			model)
				model=${arg:6}
				;;
			*)
				error "cpu: unknown arg '${arg}'"
				;;
			esac
		done
	else
		nr_cpus=${1}
	fi

	if [[ ! -z ${nr_cpus} ]]; then
		q_cpus=${nr_cpus}
	fi
	if [[ ! -z ${model} ]]; then
		q_cpu_model=${model}
	fi
}

################################################################################
# UEFI
declare -a UEFI_CODES=(
	# OVMF: Open Virtual Machine Firmware
	/usr/share/OVMF/OVMF_CODE.fd
	/usr/share/OVMF/OVMF_CODE.secboot.fd
	/usr/share/AAVMF/AAVMF_CODE.fd
)

declare -a UEFI_VARS=(
	/usr/share/OVMF/OVMF_VARS.fd
	/usr/share/AAVMF/AAVMF_VARS.fd
)

case ${ARCH} in
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
			local arg_key=${arg%%=*}
			case ${arg_key} in
			type)
				f_rootfs_type=${arg:5}
				if ! [[ " ${DISK_TYPES[@]} " =~ " ${f_rootfs_type} " ]]; then
					error "rootfs unsupport '${arg}'"
				fi
				;;
			file)
				f_rootfs=${arg:5}
				;;
			rw | ro)
				if [[ ${arg_key} != ro ]] &&
				   [[ ${arg_key} != rw ]]; then
					error "rootfs unknown ${arg}"
				fi
				k_rw=${arg_key}
				;;
			*)
				if [[ -f ${arg_key} ]]; then
					f_rootfs=${arg_key}
				else
					if [[ ${dry_run} ]]; then
						warning "rootfs maybe use wrong file '${arg_key}'"
						f_rootfs=${arg_key}
					else
						error "rootfs unknown ${arg}"
					fi
				fi
				;;
			esac
		done
		if [[ -z ${f_rootfs} ]]; then
			error "not found file for rootfs in '${args[@]}'"
		fi
	else
		f_rootfs=${1}
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

  ${BOLD}[FILE],[ro|rw]${RST}: specify disk file, see ${BOLD}[FILE]${RST}
  ${BOLD}file=<FILE>,[ro|rw]${RST}: specify disk file, see ${BOLD}[FILE]${RST}

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

# $1: vm-name
config_prepare_vm_tmpdir() {
	local name=${1}
	# If dry-run, vm temp directly will not be created, thus, just set it
	# to ${TMPDIR}.
	if [[ ${dry_run} ]]; then
		TMPDIR=/tmp
		vm_tmpdir="${TMPDIR}"
	else
		vm_tmpdir=${TMPDIR}/${name}
	fi

	vm_cmd_sh=${vm_tmpdir}/cmds.sh
	vm_port_hostfwd_ssh22=${vm_tmpdir}/port-hostfwd-ssh22.txt
	vm_port_monitor_telnet=${vm_tmpdir}/port-monitor-telnet.txt

	cxl_dry_run_log=${vm_cmd_sh}
}

################################################################################
# VM Management
__usage_list_vm__() {
	echo -e "
${BOLD}NAME${RST}
    ${PROG} list - Listing virtual machine

${BOLD}SYNOPSIS${RST}
    ${PROG} ${BOLD}list${RST} [-h|--help]

${BOLD}OPTIONS${RST}
    -a, --all      list all VMs and their information
    -p, --port     list VMs's network port
    --qemu-cmd     listing qemu command
    -h, --help     show this information
    -v, --verbose  enable verbose mode
"
	exit ${1-0}
}

list_vm() {
	local i pidfile
	local pidfiles=( $(find ${TMPDIR} -name '*.pid' 2>/dev/null) )
	local id=0
	local list_all list_port list_qemucmd
	local LIST_VM_ARGS

	LIST_VM_ARGS=$(getopt --options aphv \
		--long all \
		--long port \
		--long qemu-command \
		--long help \
		--long verbose \
		--name list-vm -- "$@")
	local status=$?
	if [[ ${status} -ne 0 ]]; then
		__usage_list_vm__ 1
	fi

	eval set -- "$LIST_VM_ARGS"

	while true; do
		case $1 in
		-h | --help)
			shift
			__usage_list_vm__
			;;
		-a | --all)
			shift
			list_port=ON
			list_qemucmd=ON
			;;
		-p | --port)
			shift
			list_port=ON
			;;
		--qemu-command)
			shift
			list_qemucmd=ON
			;;
		-v | --verbose)
			shift
			enable_verbose
			;;
		--)
			shift
			break
			;;
		esac
	done

	printf "%-4s %-16s %-8s" Id Name State
	if [[ ${list_port} ]]; then
		printf " %-8s" SSH
		printf " %-8s" TELNET
	fi
	printf "\n"
	echo -n '---------------------------------------'
	if [[ ${list_port} ]]; then
		echo -n '-------------'
	fi
	echo

	for pidfile in ${pidfiles[@]}
	do
		local name="${pidfile#${TMPDIR}/}"
		name="$(dirname ${name})"

		config_prepare_vm_tmpdir ${name}

		local pid=$(sudo cat ${pidfile})
		local state="unknown"

		if [[ -d /proc/${pid} ]]; then
			state="running"
		elif [[ ! -d /proc/${pid} ]]; then
			state="die"
		fi

		printf "%-4d %-16s %-8s" ${id} ${name} ${state}
		if [[ ${list_port} ]]; then
			printf " %-8d" $(cat ${vm_port_hostfwd_ssh22})
			printf " %-8d" $(cat ${vm_port_monitor_telnet})
		fi
		printf "\n"

		if [[ -n ${list_qemucmd} ]]; then
			printf "\033[2mQemu: "
			cat ${vm_tmpdir}/qemu-command.sh
			printf "\033[m"
		fi

		id=$((id + 1))
	done
}

# $1: virtual machine name
kill_vm() {
	local name=${1}
	local pidfile=${TMPDIR}/${name}/pidfile.pid

	if [[ ! -f ${pidfile} ]]; then
		error "Not found vm '${name}'"
	fi

	config_prepare_vm_tmpdir ${name}

	if [[ -f ${vm_port_monitor_telnet} ]]; then
		warning "Destroy ${name} with Qemu monitor"
		echo "system_powerdown" | sudo nc localhost $(cat ${vm_port_monitor_telnet})
	else
		# Kill host process is dangerous for guestos disk.
		warning "Kill ${name} process on host"
		local pid=$(sudo cat ${pidfile})
		sudo kill ${pid}
	fi

	sudo rm -rf ${vm_tmpdir}
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
		local dev_nbd=$(nbd_find_idle_dev)
		sudo qemu-nbd --connect ${dev_nbd} ${img} -f ${img_type} >/dev/null && sleep 1
		sudo lsblk -o uuid ${dev_nbd} | grep -v UUID
		sudo qemu-nbd --disconnect ${dev_nbd} >/dev/null
		sudo rmmod nbd || true >/dev/null
		;;
	*)
		error "Unknown image '${img}' extension '${img_type}'"
		;;
	esac
}

cleanup() {
	local err=$?

	# Qemu process maybe running on background, we do not need cleanup then.
	if [[ -z ${q_daemon} ]]; then
		qemu_eval sudo rm -rf ${cleanup_files[@]}
	fi

	if [[ ${err} != 0 ]] && [[ -d ${vm_tmpdir} ]]; then
		qemu_eval sudo rm -rf ${vm_tmpdir}
	fi

	if [[ ${err} != 0 ]]; then
		error "${PROG} running failed"
	fi
	exit ${err}
}

config_vm_tmpdir() {
	TCP_PORT_HOSTFWM_SSH22=$(get_free_tcp_port)
	TCP_PORT_MONITOR_TELNET=$(get_free_tcp_port)

	if [[ ! -d ${TMPDIR} ]]; then
		qemu_eval mkdir -p ${TMPDIR}
	fi

	if [[ ! -d ${vm_tmpdir} ]]; then
		qemu_eval mkdir -p ${vm_tmpdir}
	fi

	qemu_eval touch ${vm_cmd_sh}
	qemu_eval chmod +x ${vm_cmd_sh}

	if [[ -z ${dry_run} ]]; then
		fprintf ${vm_port_hostfwd_ssh22} ${TCP_PORT_HOSTFWM_SSH22}
		fprintf ${vm_port_monitor_telnet} ${TCP_PORT_MONITOR_TELNET}
	fi

	cleanup_files+=( ${vm_cmd_sh} )
	cleanup_files+=( ${vm_port_hostfwd_ssh22} )
	cleanup_files+=( ${vm_port_monitor_telnet} )
}

config_basic() {
	local pidfile=${vm_tmpdir}/pidfile.pid
	local qmpfile=${vm_tmpdir}/qmp.sock

	qargs+=( -name ${q_vm_name} )
	qargs+=( -uuid $(gen_uuid) )
	# or use '-accel kvm'
	qargs+=( -enable-kvm )
	qargs+=( -boot menu=on )

	# -qmp <protocol>:<path>[,server][,nowait]
	# -qmp unix:./qmp.sock,server,nowait
	# $ sudo socat - UNIX-CONNECT:./qmp.sock
	# Or use:
	# -qmp tcp:0.0.0.0:4444,server,nowait
	# $ telnet localhost 4444
	# Or use:
	# -qmp stdio
	qargs+=( -qmp unix:${qmpfile},server=on,wait=off )
	cleanup_files+=( ${qmpfile} )

	qargs+=( -pidfile ${pidfile})
	cleanup_files+=( ${pidfile} )

	# Qemu monitor
	# $ telnet localhost PORT
	qargs+=( -monitor tcp:localhost:${TCP_PORT_MONITOR_TELNET},server,nowait )
	# Or could use:
	# $ sudo socat - UNIX-CONNECT:./qemu-monitor-${q_vm_name}.sock
	#qargs+=( -monitor unix:./qemu-monitor-${q_vm_name}.sock,server,nowait )
	#cleanup_files+=( ./qemu-monitor-${q_vm_name}.sock )

	if [[ ${q_stdio} ]] && [[ ${q_daemon} ]]; then
		error "Could not use --stdio and --daemon at same time"
	fi

	if [[ ${q_stdio} ]]; then
		# Default TERM=vt220 if stdio, you could specify
		# TERM=xterm-256color or TERM=linux in your virtual machine.
		qargs+=( -serial mon:stdio )
		qargs+=( -nographic )
	fi

	if [[ ${q_daemon} ]]; then
		qargs+=( -daemonize )
		qargs+=( -vnc :1 )
	fi

	case ${ARCH} in
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

# IPMI BMC
config_bmc() {
	# Internal Emulation (Built-in Simulator)
	case ${ARCH} in
	x86_64)
		# ISA-Based Configuration (Standard x86 PC)
		qargs+=( -device ipmi-bmc-sim,id=bmc0
			 -device isa-ipmi-kcs,bmc=bmc0 )
		;;
	*)
		# PCI-Based Configuration
		qargs+=( -device ipmi-bmc-sim,id=bmc0
			 -device pci-ipmi-kcs,bmc=bmc0 )
		;;
	esac

	# TODO: except qemu internal emulation, external emulation has full
	# featured such as OpenIPMI "ipmi_sim".
	#qargs+=( -chardev socket,id=ipmi0,host=localhost,port=9012
	#	 -device ipmi-bmc-extern,id=bmc0,chardev=ipmi0
	#	 -device isa-ipmi-bt,bmc=bmc0 )
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
	local cpu_args=( ${q_cpu_model} )

	# Skip warning on Hygon:
	# qemu-system-x86_64: host doesn't support requested feature: vPMU
	if [[ "$(cpu_is_hygon)" ]]; then
		cpu_args+=( pmu=off )
	fi

	qargs+=( -cpu $(IFS=,; echo "${cpu_args[*]}") )
	qargs+=( -smp cpus=${q_cpus},maxcpus=$((q_cpus * 2)) )

	# TODO: support more cpu
	# qargs+=( -cpu kvm64,+kvm_pv_unhalt,+kvm-pv-ipi,+kvm-pv-tlb-flush )

	# TODO: support numa
	# -smp cpus=8,sockets=2,cores=4,threads=1
	# -numa node,nodeid=0,cpus=0-3,mem=4G
	# -numa node,nodeid=1,cpus=4-7,mem=4G
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
	if [[ ${ARCH} == aarch64 ]]; then
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
		local newvar=${vm_tmpdir}/$(basename ${var})
		qemu_eval cp ${var} ${newvar}
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
# $ ssh -p${PORT} root@localhost
# Make sure port was not used, check with:
# $ sudo netstat -tulpn | grep ${PORT}
add_net_nic_user_tap() {
	qargs+=( -net user,hostfwd=tcp::${TCP_PORT_HOSTFWM_SSH22}-:22 )
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

	kcmds+=( earlycon )
	kcmds+=( earlyprintk=serial )
	kcmds+=( net.ifnames=0 )
	kcmds+=( selinux=0 )
	kcmds+=( audit=0 )
	kcmds+=( nokaslr )

	case ${ARCH} in
	aarch64)
		# see commit 26e8c4697445 ("qemu-vm.sh: aarch64: use console=ttyAMA0")
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

	if [[ ${dry_run} ]]; then
		# fake 10G
		size=$(( 10 * 1024 * 1024 * 1024 ))
	else
		size=$(stat --format=%s ${f_img})
	fi
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

################################################################################
# Main

# Handle subcommand first
case ${1} in
list)
	shift
	list_vm "${@}"
	exit 0
	;;
destroy)
	shift
	if [[ -z ${1} ]]; then
		error "'destroy' need pass virtual name, check with '${PROG} list'"
	fi
	kill_vm "${@}"
	shift
	exit 0
	;;
-*)
	;;
*)
	error "Unknown subcommand '${1}'"
	;;
esac

set_qemu_kvm $(get_qemu_kvm_emulator)

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
	--long daemon \
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
		have_cxl=ON
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
	--daemon)
		shift
		q_daemon=ON
		;;
	-Q | --qemu)
		shift
		set_qemu_kvm $1
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
		cxl_dry_run=ON
		export DRY_RUN=${dry_run}
		;;
	-v | --verbose)
		shift
		verbose=ON
		;;
	-V | --version)
		shift
		echo "${0} ${VERSION}"
		exit 0
		;;
	-D | --debug)
		shift
		debug=ON
		handle_cxl_arg debug
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

if [[ -z ${f_kernel} ]] && [[ -z ${f_initrd} ]] && [[ -z ${f_disks} ]]; then
	error "must specify kernel and initrd, or specify one disk at least"
fi

if [[ ${verbose} ]]; then
	enable_verbose
fi

trap cleanup EXIT

config_prepare_vm_tmpdir ${q_vm_name}
config_vm_tmpdir
config_basic
config_bmc
config_memory
config_cpu
config_uefi
config_pci
config_net
config_kernel
config_rootfs
config_disk
config_nvdimm
[[ -n ${have_cxl} ]] && config_cxl
config_virtiofs

[[ -n ${have_cxl} ]] && qmachine+=( "${cxl_qmachine[@]}" )
qmachine=( $(printf "%s\n" ${qmachine[@]} | sort -u) )
[[ -n ${have_cxl} ]] && qargs+=( ${cxl_qargs[@]} )
qargs+=( -machine $(IFS=,; echo "${qmachine[*]}") )
[[ -n ${have_cxl} ]] && kcmds+=( "${cxl_kcmds[@]}" )

qemucmd=${vm_tmpdir}/qemu-command.sh
echo "${QEMU} ${qargs[@]} ${kcmds:+-append \"${kcmds[@]}\"}" > >(sudo tee ${qemucmd})
qemu_eval ${QEMU} ${qargs[@]} ${kcmds:+-append \"${kcmds[@]}\"}
