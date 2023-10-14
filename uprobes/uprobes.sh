#!/bin/bash

TRACEFS=/sys/kernel/debug/tracing/

binary=/bin/bash
func=readline

if [[ $(id -u) != 0 ]]; then
	echo "ERROR: Must run with root(sudo)"
	exit 1
fi

binary=$( realpath ${binary} )
addr=$(
	objdump -T ${binary} | grep -w ${func} | awk '{print $1}' || {
		echo "ERROR: Not found ${func} in ${binary}"
		exit 1
	}
)

echo "p:uprobes/${func} ${binary}:0x${addr} %ip %ax" > ${TRACEFS}/uprobe_events
cat ${TRACEFS}/events/uprobes/${func}/format

echo 1 > ${TRACEFS}/events/uprobes/enable

clean() {
	echo 0 > ${TRACEFS}/events/uprobes/enable
	echo > ${TRACEFS}/uprobe_events
}
trap clean EXIT

watch -n1 tail ${TRACEFS}/trace


