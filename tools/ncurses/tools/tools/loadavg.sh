#!/bin/bash
# display the loadavg
set -e

while sleep 1; do
	awk '{print $1, $2, $3}' /proc/loadavg
done | ../plotcake ${args[@]} --title 'Loadavg' --xlabel 'Time' --ylabel 'Load' \
		-l 'Load1' -l 'Load5' -l 'Load15'
