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

if $(cmdline_bool ignition.firstboot 0); then
	echo "ignition.firstboot on"
else
	echo "ignition.firstboot off"
fi
