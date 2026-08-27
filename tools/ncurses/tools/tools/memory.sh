#!/bin/bash
# display the memory usage
set -e

while true; do
	free -m | grep ^Mem | awk '{print $2, $3, $4, $5, $6, $7}'
	sleep 1
done | ../plotcake ${args[@]} --title 'Memory Usage' --xlabel 'Time' --ylabel 'Size(MB)' \
		-l total -l used -l free -l shared -l buff/cache -l avail \
		-o memory ${@}
