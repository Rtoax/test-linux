#!/bin/bash
# display one storage read and write
set -e

iostat_x() {
	iostat | grep -e ^sd -e ^nvme -e ^vd | head -1
}

if which iostat 2>&1 >/dev/null; then
	while sleep 1; do
		iostat_x | awk '{print $3, $4}'
	done | ../plotcake ${args[@]} -T "$(iostat_x | awk '{print $1}') Read-Write" \
			-l 'kB_read/s' -l 'kB_wrtn/s' --ylabel 'Rate' ${@}
fi
