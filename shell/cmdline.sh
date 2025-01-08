#!/bin/bash
set -e

cmdline=( $(</proc/cmdline) "$@" )

cmdline_arg() {
	local name value arg
	name=$1
	value=$2

	for arg in "${cmdline[@]}"
	do
		if [[ "${arg%%=*}" == "${name}" ]]; then
			value="${arg#*=}"
		fi
	done
	echo "${value}"
}

cmdline_bool() {
	local value=$(cmdline_arg "$@")
	case "${value}" in
	""|0|no|off) return 1;;
	*) return 0;;
	esac
}

__main__()
{
	if $(cmdline_bool ignition.firstboot 0); then
		echo "ignition.firstboot on"
	else
		echo "ignition.firstboot off"
	fi
}

__main__ ignition.firstboot=1
__main__ ignition.firstboot=0
__main__ ignition.firstboot=on
__main__ ignition.firstboot=off
__main__ ignition.firstboot
