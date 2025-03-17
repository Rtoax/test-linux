#!/bin/bash
set -e

dev_raid_metadata() {
	local dev=$1
	# -E, --examine Print contents of the metadata stored on the named device(s)
	sudo mdadm --examine ${dev}
	# formatted as key=value pairs
	sudo mdadm --examine --export ${dev}
}

find_raid() {
	echo "------------------------------ lspci ------------------------------------"
	sudo lspci | grep RAID | sed 's/^/LSPCI: /g'
	echo "------------------------------- lshw ------------------------------------"
	sudo lshw -class storage | grep '\-raid' -A11 | sed 's/^/LSHW: /g'
	echo "------------------------------- /proc/scsi/scsi--------------------------"
	sudo cat /proc/scsi/scsi | grep -i raid
	echo "-------------------------------------------------------------------------"
}

software_raid_info() {
	sudo cat /proc/mdstat
	[[ -e /dev/md0 ]] && sudo mdadm -D /dev/md0
}

find_raid
dev_raid_metadata /dev/sda
software_raid_info

