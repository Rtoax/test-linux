#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.

readonly LIBQEMU_IPMI_VERSION="v0.0.1"

declare -a ipmi_qargs

# IPMI BMC
config_bmc() {
	# Internal Emulation (Built-in Simulator)
	case ${ARCH} in
	x86_64)
		# ISA-Based Configuration (Standard x86 PC)
		ipmi_qargs+=( -device ipmi-bmc-sim,id=bmc0
				-device isa-ipmi-kcs,bmc=bmc0 )
		;;
	*)
		# PCI-Based Configuration
		ipmi_qargs+=( -device ipmi-bmc-sim,id=bmc0
				-device pci-ipmi-kcs,bmc=bmc0 )
		;;
	esac

	# TODO: except qemu internal emulation, external emulation has full
	# featured such as OpenIPMI "ipmi_sim".
	#ipmi_qargs+=( -chardev socket,id=ipmi0,host=localhost,port=9012
	#		-device ipmi-bmc-extern,id=bmc0,chardev=ipmi0
	#		-device isa-ipmi-bt,bmc=bmc0 )
}
