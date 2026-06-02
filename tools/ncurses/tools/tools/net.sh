#!/bin/bash
# display the NIC rx and tx
set -e

# TODO: the bytes is too large to show the changes.
iface=( $(cat /proc/net/dev | grep ':' | awk '{print $1}') )
maxbytes=0
# found the most busy nic
for i in ${iface[@]}; do
	bytes=$(grep ${i} /proc/net/dev | awk '{print $2}')
	if [[ ${maxbytes} -lt ${bytes} ]]; then
		maxbytes=${bytes}
		maxiface=${i}
	fi
done
while sleep 1; do
	grep ${maxiface} /proc/net/dev | awk '{print $2, $10}'
done | ../plotcake ${args[@]} --title "${maxiface} tx/rx" --logarithmic \
		-l RX -l TX
