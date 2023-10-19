#!/bin/bash

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
	echo "-------------------------------------------------------------------------"
}

find_raid
dev_raid_metadata /dev/sda

