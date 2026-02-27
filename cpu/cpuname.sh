#!/bin/bash
# This script only display CPU name, do not display other anything else, and
# don't execute failed, because the git/hooks will use it.
set -e

cpuname() {
	readonly CPU_MODEL=$(lscpu | grep -e "^Model name" -e "^型号名称" | \
			awk '{ for(i=3; i<=NF; i++) printf "%s", $i (i==NF ? "\n" : " ") }')
	readonly CPU_VENDOR=$(lscpu | grep -e "^Vendor ID" -e "^厂商 ID" | \
			awk '{ for(i=3; i<=NF; i++) printf "%s", $i (i==NF ? "\n" : " ") }')
	if [[ ${CPU_MODEL} ]]; then
		echo ${CPU_MODEL}
	elif [[ ${CPU_VENDOR} ]]; then
		echo ${CPU_VENDOR}
	else
		fatal "Can't get cpu info from lscpu"
	fi
}

cpuname
