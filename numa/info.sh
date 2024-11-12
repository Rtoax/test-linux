#!/bin/bash
set -e

# Match format: 'node   0: mem 0x0000000000001000-0x000000000009efff]'
dmesg_node_mem_raw()
{
	sudo dmesg | \
		grep -oe "node[[:space:]]\{1,\}[[:digit:]]\{1,2\}: \[mem 0x[0-9a-fA-F]\{16\}-0x[0-9a-fA-F]\{16\}\]"
}

case $1 in
raw)
	dmesg_node_mem_raw
	;;
*)
	echo >&2 "Usage: $0 [raw]"
	;;
esac
