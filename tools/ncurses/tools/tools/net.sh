#!/bin/bash
# display the NIC rx and tx
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

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
while true; do
	grep ${maxiface} /proc/net/dev | awk '{print $2, $10}'
	sleep 1
done | ${PLOTCAKE} --title "${maxiface} tx/rx" --logarithmic \
		-l RX -l TX -o net ${@}
