#!/bin/bash
set -e

readonly WHERE_AM_I=$(dirname $(realpath $0))
. ${WHERE_AM_I}/../libqemu.sh
. ${WHERE_AM_I}/libversion.sh

QEMU_KVM=$(get_qemu_kvm_emulator)
if [[ -z ${QEMU_KVM} ]]; then
	echo >&2 "ERROR: not found QEMU in your system"
	exit 0
fi

version=$(${QEMU_KVM} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' | head -1)

version_parser ${@} -- ${version}
