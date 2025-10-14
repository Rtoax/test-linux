#!/bin/bash
set -e

TRACEFS=/sys/kernel/debug/tracing/

binary=/bin/bash
func=readline

if [[ $(id -u) != 0 ]]; then
	echo "ERROR: Must run with root(sudo)"
	exit 1
fi

binary=$( realpath ${binary} )
# WARNING: This address is in binary address, not PIE real address.
addr=$( objdump -T ${binary} | grep -w ${func} 2>/dev/null | awk '{print $1}' )

[[ ! -e ${binary} ]] && echo "ERROR: ${binary} is not exist" && exit 1
[[ -z ${addr} ]] && echo "ERROR: Not found ${func} in ${binary}" && exit 1

readelf -h ${binary} | grep 'Type:'

echo "p:uprobes/${func} ${binary}:0x${addr} %ip %ax" | sudo tee ${TRACEFS}/uprobe_events

cat ${TRACEFS}/events/uprobes/${func}/format
cat ${TRACEFS}/events/uprobes/${func}/enable

echo 1 | sudo tee ${TRACEFS}/events/uprobes/enable

cleanup() {
	local ret=$?
	echo 0 | sudo tee ${TRACEFS}/events/uprobes/enable
	echo | sudo tee ${TRACEFS}/uprobe_events
	exit ${ret}
}
trap cleanup EXIT

watch -n1 tail ${TRACEFS}/trace
