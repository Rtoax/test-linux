#!/bin/bash
# This script only display uefi version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: uefi.sh [--specmajor|--specminor|--vendor]
#
set -e

if [[ ! -d /sys/firmware/efi/ ]]; then
	exit 1
fi

# UEFI Specification Version
spec_version=$(sudo dmesg | grep -i "EFI v" | grep -Eo 'v[0-9]+\.[0-9]+')

# Motherboard vendor
bios_vendor=$(cat /sys/class/dmi/id/bios_vendor)
bios_release=$(cat /sys/class/dmi/id/bios_release)
bios_version=$(cat /sys/class/dmi/id/bios_version)

case $1 in
--specmajor)
	echo ${spec_version%%.*} | tr -d v
	;;
--specminor)
	echo ${spec_version##*.}
	;;
--vendor)
	echo "${bios_vendor} ${bios_release}(${bios_version})"
	;;
"")
	echo ${spec_version}
	;;
*)
	exit 1
	;;
esac
