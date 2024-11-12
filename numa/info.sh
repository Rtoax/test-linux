#!/bin/bash
set -e

# Match format: 'node   0: mem 0x0000000000001000-0x000000000009efff]'
dmesg_node_mem_raw()
{
	sudo dmesg | \
		grep -oe "node[[:space:]]\{1,\}[[:digit:]]\{1,2\}: \[mem 0x[0-9a-fA-F]\{16\}-0x[0-9a-fA-F]\{16\}\]"
}

dmesg_node_mem_pure()
{
	dmesg_node_mem_raw | tr '[:\-]' ' '
}

case $1 in
raw)
	dmesg_node_mem_raw
	;;
pure)
	dmesg_node_mem_pure
	;;
*)
	echo >&2 "Usage: $0 [raw|pure]"
	exit 1
	;;
esac
