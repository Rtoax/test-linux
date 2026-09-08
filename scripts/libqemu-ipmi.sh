#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.

readonly LIBQEMU_IPMI_VERSION="v0.0.3"
readonly LIBQEMU_IPMI_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

declare -a ipmi_qargs

. ${LIBQEMU_IPMI_ROOT}/libqemu.sh

ipmi_check_device() {
	local qemu=$(get_qemu_kvm_emulator)

	if [[ "$(timeout 0.5 ${qemu} -machine virt --nographic "${@}" 2>&1 | \
			grep 'is not a valid device model name')" ]]; then
		return
	fi
	echo YES
}

# Config IPMI BMC
# $1: CPU architecture
config_bmc() {
	local _arch=$1
	local pci_ipmi_kcs_qargs=( -device ipmi-bmc-sim,id=bmc0
				-device pci-ipmi-kcs,bmc=bmc0 )

	# Internal Emulation (Built-in Simulator)
	case ${_arch} in
	x86_64)
		# ISA-Based Configuration (Standard x86 PC)
		ipmi_qargs+=( -device ipmi-bmc-sim,id=bmc0
				-device isa-ipmi-kcs,bmc=bmc0 )
		;;
	*)
		# PCI-Based Configuration
		if [[ $(ipmi_check_device ${pci_ipmi_kcs_qargs[@]}) == YES ]]; then
			ipmi_qargs+=( ${pci_ipmi_kcs_qargs[@]} )
		fi
		;;
	esac

	# TODO: except qemu internal emulation, external emulation has full
	# featured such as OpenIPMI "ipmi_sim".
	#ipmi_qargs+=( -chardev socket,id=ipmi0,host=localhost,port=9012
	#		-device ipmi-bmc-extern,id=bmc0,chardev=ipmi0
	#		-device isa-ipmi-bt,bmc=bmc0 )
}
