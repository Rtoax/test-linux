#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# CXL
#
# - CXL level: PCIe.0 -> pxb-cxl -> cxl-rp -> [cxl-switch] -> cxl-type3
#
# - CXL fmw: Fixed Memory Window
# - CXL pxb (PCIe eXpander Bridge)
#           $ qemu-kvm -device pxb-cxl,...
#           see commit b4271dd6068b ("qemu: cxl-pxb: 'lspci -tv'")
# - CXL rp (Root Port)
#           $ qemu-kvm -device cxl-rp,...
#           see commit f6f541dae696 ("qemu: cxl-rp(root-port): 'lspci -tv'")
# - CXL Switch
#           $ qemu-kvm -device cxl-upstream,... -device cxl-downstream,...
#           see commit 559bfebf5d44 ("qemu: cxl-switch: 'lspci -tv'")
# - CXL Device
#           $ qemu-kvm -device cxl-type3,...,persistent-memdev=...
#           see commit 445c8c03b035 ("qemu: cxl-type3: persistent-memdev: lspci, acpi")
#
#           $ qemu-kvm -device cxl-type3,...,volatile-memdev=...
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

readonly LIBQEMU_CXL_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBQEMU_CXL_ROOT}/liblog.sh
. ${LIBQEMU_CXL_ROOT}/libstring.sh

declare -a cxl_qargs cxl_qmachine cxl_kcmds
declare cxl_debug cxl_dry_run cxl_dry_run_log

readonly CXL_DEV_VMEM=cxl-vmem
readonly CXL_DEV_VMEM_DC=cxl-vmem-dc
readonly CXL_DEV_VMEM_LSA=cxl-vmem-lsa
readonly CXL_DEV_VMEM_LSA_DC=cxl-vmem-lsa-dc
readonly CXL_DEV_VMEM_4WAY=cxl-vmem-4way
readonly CXL_DEV_VMEM_4WAY_DC=cxl-vmem-4way-dc
readonly CXL_DEV_VMEM_4WAY_SWITCH=cxl-vmem-4way-switch
readonly CXL_DEV_VMEM_4WAY_SWITCH_DC=cxl-vmem-4way-switch-dc
readonly CXL_DEV_PMEM=cxl-pmem
readonly CXL_DEV_PMEM_4WAY=cxl-pmem-4way
readonly CXL_DEV_PMEM_4WAY_SWITCH=cxl-pmem-4way-switch
readonly CXL_BUILTIN_DEVICES=( ${CXL_DEV_VMEM}
			       ${CXL_DEV_VMEM_DC}
			       ${CXL_DEV_VMEM_LSA}
			       ${CXL_DEV_VMEM_LSA_DC}
			       ${CXL_DEV_VMEM_4WAY}
			       ${CXL_DEV_VMEM_4WAY_DC}
			       ${CXL_DEV_VMEM_4WAY_SWITCH}
			       ${CXL_DEV_VMEM_4WAY_SWITCH_DC}
			       ${CXL_DEV_PMEM}
			       ${CXL_DEV_PMEM_4WAY}
			       ${CXL_DEV_PMEM_4WAY_SWITCH} )

declare -a cxl_fmw=( 0 ) # (0 1 2 3)

# cxl-pxb specify id=, this is CHBS(CXL Host Bridge Structure)
# and use to -machine cxl-fmw.0.targets.M
declare -a cxl_pxb_ids # ( pxb-id1 pxb-id2 ... )
declare -A cxl_pxb_fmw # arr[pxb-id]=0, default is 0
declare -A cxl_pxb_sizes # arr[pxb-id]=2G
declare -A cxl_pxb2rps # arr[pxb-id]="rp-id1 rp-id2 ..."
declare __cxl_pxb_next_bus_nr=11 # bus_nr=11,21,31,41,...

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
declare __cxl_next_slot=1

# cxl type3 devices
declare -a cxl_pmem_names # arr=( name1 name2 ... )
declare -A cxl_pmem_bus # arr[name]=BUS
declare -A cxl_pmem_lsa # arr[name]=LSA
declare -A cxl_pmem_size # arr[name]=SIZE
declare -a cxl_vmem_names # arr=( name1 name2 ... )
declare -A cxl_vmem_bus # arr[name]=BUS
declare -A cxl_vmem_lsa # arr[name]=LSA
declare -A cxl_vmem_dc # arr[name]=[ON]
declare -A cxl_vmem_size # arr[name]=SIZE
# use to find root port id or switch downstream id of cxl-type3
declare -A cxl_pvmem_id2bus # arr[type3-id]=[rp-id|switch-downstream-id]
declare -A cxl_pvmem_id2name # arr[type3-id]=NAME in cxl_pmem_names[]
declare -a cxl_pvmem_ids # ( id1 id2 ... )

declare cxl_device
readonly CXL_DEFAULT_MSIZE=1024M
# display cxl device topology before vm startup
declare cxl_show_topology

cxl_eval()
{
	DRY_RUN=${cxl_dry_run} DRY_RUN_LOG=${cxl_dry_run_log} dry_run "${@}"
}

cxl_arg_help() {
	echo -e "
${BOLD}CXL ARGUMENTS SYNTAX${RST}

${BOLD}--cxl [help|?]${RST}: show this information

${BOLD}--cxl [DEVICE]${RST}: see ${BOLD}[DEVICE]${RST} section below
${BOLD}--cxl <device|dev>=[DEVICE|<list|?>]${RST}: see ${BOLD}[DEVICE]${RST} section below

${BOLD}--cxl pxb=<name>,[fmw|fixed-memory-window=<N>]${RST}: create CXL PXB, fmw default 0
${BOLD}--cxl <root-port|rp>=<name>,bus=<name>,port=<num>${RST}: create CXL RootPort
${BOLD}--cxl switch,bus=<name>,nport=<num>,portprefix=<name>${RST}: create CXL Switch
${BOLD}--cxl pmem=<name>,bus=<name>,lsa=<name>,[size=<SIZE>]${RST}: create CXL Persistent Memory device
${BOLD}--cxl vmem=<name>,bus=<name>,[lsa=<name>],[size=<SIZE>],[dc|dynamic-capacity]${RST}: create CXL Volatile Memory device

${BOLD}--cxl show=[topo]${RST}: display CXL information before vm startup, will not startup vm

${BOLD}[DEVICE]${RST}
${GRAY}${CXL_BUILTIN_DEVICES[@]}${RST}

${BOLD}FORMAT${RST}

  ${FORMAT_SIZE}
"
	exit 0
}

handle_cxl_arg() {
	local arg args
	local device
	local pxb_id pxbfmw=0
	local bus port
	local rp_id
	local switch nport portprefix
	local pmem vmem lsa size
	local enable_dc

	# Pre handle
	args=( $(echo $1 | tr ',' ' ') )
	for arg in ${args[@]}
	do
		case ${arg%%=*} in
		help|?)
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
			dev)
				device=${arg:4}
				;;
			pxb)
				pxb_id=${arg:4}
				;;
			fmw|fixed-memory-window)
				if [[ ${arg:0:3} == fmw ]]; then
					pxbfmw=${arg:4}
				elif [[ ${arg:0:19} == fixed-memory-window ]]; then
					pxbfmw=${arg:20}
				else
					error "cxl: bad fmw '${arg}'"
				fi
				if ! [[ " 0 1 2 3 4 5 " =~ " ${pxbfmw} " ]]; then
					error "bad cxl pxb ${arg} only support 0 1 2 3 4 5"
				fi
				;;
			rp|root-port)
				if [[ ${arg:0:2} == rp ]]; then
					rp_id=${arg:3}
				elif [[ ${arg:0:9} == root-port ]]; then
					rp_id=${arg:10}
				else
					error "cxl: bad root-port '${arg}'"
				fi
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
			dc|dynamic-capacity)
				enable_dc=ON
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
					error "cxl: not support show= syntax"
					;;
				esac
				;;
			*)
				error "cxl: unknown arg ${arg}"
				;;
			esac
		done
	else
		device=$1
	fi

	if [[ ${device} ]] && [[ ${pxb_id} ]]; then
		error "cxl: not allow specify pxb= for device"
	fi

	if [[ ${device} ]] && [[ ${rp_id} ]]; then
		error "cxl: not allow specify rp= for device"
	fi

	if [[ ${device} ]] && [[ ${switch} ]]; then
		error "cxl: not allow specify switch for device"
	fi

	if [[ ${device} ]] && [[ ${pmem}${vmem} ]]; then
		error "cxl: not allow specify pmem or vmem for device"
	fi

	local types=( ${pxb_id} ${rp_id} ${switch} ${vmem} ${pmem} )

	if [[ ${#types[@]} -gt 1 ]]; then
		error "cxl: not allow specify pxb,rp,switch,vmem,pmem at the same time"
	fi

	if [[ ${rp_id} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${port} ]]; then
			error "cxl: rp need bus= port= at the same time"
		fi
	fi

	if [[ ${switch} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${nport} ]] || [[ -z ${portprefix} ]]; then
			error "cxl: switch need bus= nport= portprefix= at the same time"
		fi
	fi

	if [[ ${pmem} ]]; then
		if [[ -z ${bus} ]] || [[ -z ${lsa} ]]; then
			error "cxl: pmem/vmem need bus= and lsa= parameter"
		fi
		if [[ ${enable_dc} == ON ]]; then
			error "cxl: pmem not support dynamic capacity yet, please check qemu upstream!"
		fi
	fi

	if [[ ${vmem} ]]; then
		if [[ -z ${bus} ]]; then
			error "cxl: vmem need bus= parameter"
		fi
	fi

	# set global
	if [[ ${device} ]]; then
		case ${device} in
		list|?)
			echo ${CXL_BUILTIN_DEVICES[@]}
			exit 0
			;;
		esac
		cxl_device=${device}
	fi

	if [[ ${pxb_id} ]]; then
		if [[ " ${cxl_pxb_ids[@]} " =~ " ${pxb_id} " ]]; then
			error "cxl: could not create pxb '${pxb_id}' twice"
		fi
		cxl_pxb_ids+=( ${pxb_id} )
		cxl_pxb_fmw[$pxb_id]=${pxbfmw}
	fi

	if [[ ${rp_id} ]]; then
		cxl_rp_ids+=( ${rp_id} )
		cxl_rp_buss+=( ${bus} )
		cxl_rp_ports+=( ${port} )
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
		cxl_vmem_dc[$vmem]=${enable_dc}
		[[ -z ${size} ]] && size=${CXL_DEFAULT_MSIZE}
		cxl_vmem_size[$vmem]=${size}
	fi

	# 2 spaces for empty cxl_device.
	if ! [[ "  ${CXL_BUILTIN_DEVICES[@]} " =~ " ${cxl_device} " ]]; then
		error "CXL not support device '${cxl_device}', support <${CXL_BUILTIN_DEVICES[@]}>"
	fi
}

next_pxb_cxl_id() {
	echo $(mktemp -u cxl.pxb.XXXX)
}

next_cxl_rp_id() {
	echo $(mktemp -u cxl.rp.XXXX)
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
	arg+=( bus_nr=${__cxl_pxb_next_bus_nr} )
	__cxl_pxb_next_bus_nr=$((__cxl_pxb_next_bus_nr + 10))

	cxl_qargs+=( -device $(IFS=,; echo "${arg[*]}") )

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

# create a cxl root port
# $1: bus (cxl pxb id)
# $2: id, root port id, maybe generated by next_cxl_rp_id()
# $3: port
add_cxl_root_port() {
	local bus=$1
	local id=$2
	local port=$3

	local arg

	arg+=( cxl-rp )
	arg+=( port=${port} )
	arg+=( bus=${bus} )
	arg+=( id=${id} )
	arg+=( chassis=0 )
	arg+=( slot=${__cxl_next_slot} )
	__cxl_next_slot=$((__cxl_next_slot + 1))

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

	cxl_qargs+=( -device $(IFS=,; echo "${arg[*]}") )
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
	local TEMP

	TEMP=$(getopt \
		--options B: \
		--long bus: \
		--long nport: \
		--long port-prefix: \
		-n $0 -- "$@")
	local status=$?
	if [[ ${status} -ne 0 ]]; then
		error "$0 parse arguments failed, ${@}"
	fi

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

	cxl_qargs+=( -device cxl-upstream,bus=${bus},id=${up_id} )

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
		dsarg+=( slot=${__cxl_next_slot} )
		__cxl_next_slot=$((__cxl_next_slot + 1))

		# Each cxl switch downstream has a upstream, on upstream has
		# not only one downstream.
		cxl_switch_down2up[${down_id}]="${up_id}"
		cxl_switch_up2downs[${up_id}]+=" ${down_id}"

		cxl_qargs+=( -device $(IFS=,; echo "${dsarg[*]}") )
		unset dsarg
	done
}

# cxl type3 device
# --pmem <name>: set pmem name
# --vmem <name>: set vmem name
# --bus <name>: set bus
# --lsa <name>: set lsa, skip if 'SKIP'
# --dynamic-capacity,--dc: enable Dynamic Capacity
add_cxl_type3_dev() {
	local arg tmparg
	local pmem vmem name
	local bus lsa
	local size
	local enable_dc
	local TEMP

	TEMP=$(getopt \
		--options t: \
		--long pmem: \
		--long vmem: \
		--long bus: \
		--long lsa: \
		--long size: \
		--long dynamic-capacity --long dc \
		-n $0 -- "$@")
	local status=$?

	if [[ ${status} -ne 0 ]]; then
		error "$0 parse arguments failed, ${@}"
	fi

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
		--dynamic-capacity | --dc)
			enable_dc=ON
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
		# if use CXL_BUILTIN_DEVICES[], cxl_pmem_size[] will be empty,
		# so, we just set it here.
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

		local pmem_file=${vm_tmpdir}/${pmem}.raw
		cxl_eval qemu-img create -f raw ${pmem_file} ${size}
		cleanup_files+=( ${pmem_file} )

		name=${pmem}

		tmparg+=( memory-backend-file )
		tmparg+=( id=${pmem} )
		tmparg+=( share=on )
		tmparg+=( mem-path=${pmem_file} )
		tmparg+=( size=${size} )
		cxl_qargs+=( -object $(IFS=,; echo "${tmparg[*]}") )
		unset tmparg
	fi

	if [[ ${vmem} ]]; then
		# volatile memory size cxl_vmem_size[] set in arguments first,
		# if use CXL_BUILTIN_DEVICES[], cxl_vmem_size[] will be empty,
		# so, we just set it here.
		if [[ ! -z ${cxl_vmem_size[$vmem]} ]]; then
			if [[ $(sizeceilfmt ${size}) != $(sizeceilfmt ${cxl_vmem_size[$vmem]}) ]]; then
				error "vmem set different size ${size} and ${cxl_vmem_size[$vmem]}"
			fi
		else
			cxl_vmem_size[$vmem]=${size}
		fi

		name=${vmem}
		cxl_qargs+=( -object memory-backend-ram,id=${vmem},share=on,size=${size} )

		if [[ ${enable_dc} ]]; then
			# commit 427db24ccb54 ("qemu-vm.sh: cxl: add volatile-dc-memdev support")
			arg+=( volatile-dc-memdev=${vmem} )
			arg+=( num-dc-regions=2 )
		else
			arg+=( volatile-memdev=${vmem} )
		fi
	fi

	if [[ ${lsa} ]] && [[ ${lsa} != SKIP ]]; then
		arg+=( lsa=${lsa} )

		local lsa_file=${vm_tmpdir}/${lsa}.raw
		cxl_eval qemu-img create -f raw ${lsa_file} ${size}
		cleanup_files+=( ${lsa_file} )

		tmparg+=( memory-backend-file,id=${lsa} )
		tmparg+=( share=on )
		tmparg+=( mem-path=${lsa_file} )
		tmparg+=( size=${size} )
		cxl_qargs+=( -object $(IFS=,; echo "${tmparg[*]}") )
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
		error "add cxl type3 device '${name}' to non exist rootport or switch"
	fi

	arg+=( id=${type3_id} )
	# Hope it will not conflict
	arg+=( sn=$RANDOM )

	cxl_qargs+=( -device $(IFS=,; echo "${arg[*]}") )
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

		add_cxl_root_port ${pxb_id1} ${rp_id} ${i}

		# Or could add it to CXL switch
		add_cxl_type3_dev --pmem=$(next_cxl_pmem_id) --bus=${rp_id} \
			--lsa=cxl-pmem-lsa${i}
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

	add_cxl_root_port ${pxb_id} ${rp_id1} 0
	add_cxl_root_port ${pxb_id} ${rp_id2} 1

	add_cxl_switch --bus=${rp_id1} --nport=4 --port-prefix=swport

	for i in $(seq 1 1 4)
	do
		add_cxl_type3_dev --pmem=$(next_cxl_pmem_id) --bus=swport.${i} \
			--lsa=cxl-pmem-lsa${i}
	done
}

# usage: <ways> [lsa|dc]
__cxl_volatile_mem_lsa() {
	local ways=${1}
	local arg
	local LSA DC

	for arg in ${@}; do
		case ${arg} in
		lsa)
			LSA=ON
			;;
		dc)
			DC="--dynamic-capacity"
			;;
		esac
	done

	local pxb_id=$(next_pxb_cxl_id)

	add_cxl_pxb ${pxb_id}

	for i in $(seq 1 1 ${ways})
	do
		local rp_id=$(next_cxl_rp_id)

		add_cxl_root_port ${pxb_id} ${rp_id} ${i}

		add_cxl_type3_dev --vmem=$(next_cxl_vmem_id) --bus=${rp_id} \
			${LSA:+--lsa cxl-vmem-lsa${i}} ${DC}
	done
}

cxl_volatile_mem() {
	__cxl_volatile_mem_lsa 1
}

cxl_volatile_mem_dc() {
	__cxl_volatile_mem_lsa 1 dc
}

cxl_volatile_mem_lsa() {
	__cxl_volatile_mem_lsa 1 lsa
}

cxl_volatile_mem_lsa_dc() {
	__cxl_volatile_mem_lsa 1 lsa dc
}

cxl_volatile_mem_4way() {
	__cxl_volatile_mem_lsa 4
}

cxl_volatile_mem_4way_dc() {
	__cxl_volatile_mem_lsa 4 lsa dc
}

__cxl_volatile_mem_4way_switch() {
	local pxb_id=$(next_pxb_cxl_id)
	local rp_id1=$(next_cxl_rp_id)
	local rp_id2=$(next_cxl_rp_id)
	local arg
	local DC LSA

	for arg in ${@}; do
		case ${arg} in
		lsa)
			LSA=ON
			;;
		dc)
			DC="--dynamic-capacity"
			;;
		esac
	done

	add_cxl_pxb ${pxb_id}

	add_cxl_root_port ${pxb_id} ${rp_id1} 0
	add_cxl_root_port ${pxb_id} ${rp_id2} 1

	add_cxl_switch --bus=${rp_id1} --nport=4 --port-prefix swport

	for i in $(seq 1 1 4)
	do
		add_cxl_type3_dev --vmem=$(next_cxl_vmem_id) --bus=swport.${i} \
			${LSA:+--lsa cxl-vmem-lsa${i}} ${DC}
	done
}

cxl_volatile_mem_4way_switch() {
	__cxl_volatile_mem_4way_switch
}

cxl_volatile_mem_4way_switch_dc() {
	__cxl_volatile_mem_4way_switch dc
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

	# FIXME: only x86_64 q35 support cxl now
	case ${ARCH} in
	aarch64)
		warning "cxl: not support ${ARCH} yet! Please check your qemu version."
		return 0
		;;
	*)
		cxl_qmachine+=( cxl=on )
		;;
	esac

	cxl_qmachine+=( nvdimm=on )

	# Create CXL PXB
	for i in ${cxl_pxb_ids[@]}
	do
		add_cxl_pxb ${i} ${cxl_pxb_fmw[$i]}
	done

	# Create CXL RootPort
	for ((i = 0; i < ${#cxl_rp_ids[@]}; i++))
	do
		add_cxl_root_port ${cxl_rp_buss[i]} ${cxl_rp_ids[i]} \
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
			--size=${cxl_vmem_size[$vmem]} \
			${cxl_vmem_dc[$vmem]:+--dynamic-capacity}
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
	${CXL_DEV_VMEM_DC})
		cxl_volatile_mem_dc
		;;
	${CXL_DEV_VMEM_LSA})
		cxl_volatile_mem_lsa
		;;
	${CXL_DEV_VMEM_LSA_DC})
		cxl_volatile_mem_lsa_dc
		;;
	${CXL_DEV_VMEM_4WAY})
		cxl_volatile_mem_4way
		;;
	${CXL_DEV_VMEM_4WAY_DC})
		cxl_volatile_mem_4way_dc
		;;
	${CXL_DEV_VMEM_4WAY_SWITCH})
		cxl_volatile_mem_4way_switch
		;;
	${CXL_DEV_VMEM_4WAY_SWITCH_DC})
		cxl_volatile_mem_4way_switch_dc
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
				cxl_qmachine+=( cxl-fmw.${j}.targets.${k}=${pxb_id} )
				k=$(expr $k + 1)
				# calulate fmw size
				fmwsz=$(sizesum ${fmwsz} ${cxl_pxb_sizes[$pxb_id]})
			fi
		done

		# align 256MiB
		fmwsz=$(sizeceilfmt ${fmwsz})
		[[ -z ${fmwsz} ]] && error "cxl: failed to get pxb size sum"
		cxl_qmachine+=( cxl-fmw.${j}.size=${fmwsz} )

		# 256, 512, 1k, 2k, 4k, 8k, 16k, default 256
		cxl_qmachine+=( cxl-fmw.${j}.interleave-granularity=4k )
	done

	# config kenrel cmdlines of cxl
	if [[ ! -z "${cxl_device}${cxl_pxb_ids}" ]]; then
		if [[ ${cxl_debug} ]]; then
			cxl_kcmds+=( "cxl_acpi.dyndbg=+fplm"
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
		# cxl_kcmds+=( acpi=off )
		cxl_kcmds+=( cxl.mem=disable )
		cxl_kcmds+=( cxl.acpi=0 )
	fi
}
