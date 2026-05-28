#!/bin/bash
# -m: (set -o monitor) monitor mode
set -em

args=( --tmout 2 )

# loadavg will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed, just for test in Build.mk's
# `prog-y`.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

# display the loadavg
while sleep .1; do
	awk '{print $1, $2, $3}' /proc/loadavg
done | ./loadavg ${args[@]} --title 'Loadavg' --xlabel 'Time' --ylabel 'Load' \
		-l 'Load1' -l 'Load5' -l 'Load15'

# display the memory usage
while sleep .1; do
	free -m | grep ^Mem | awk '{print $2, $3, $4, $5, $6, $7}'
done | ./loadavg ${args[@]} --title 'Memory Usage' --xlabel 'Time' --ylabel 'Size(MB)' \
		-l total -l used -l free -l shared -l buff/cache -l avail

# display the process number
while sleep .1; do
	ls /proc/ | grep -E '[0-9]+' | wc -w
done | ./loadavg ${args[@]} --title 'Process Number' --xlabel 'Time' --ylabel 'Number' \
		-l Proc

# display one storage read and write
iostat_x() {
	iostat | grep -e ^sd -e ^nvme -e ^vd | head -1
}
if which iostat 2>/dev/null; then
	while sleep .1; do
		iostat_x | awk '{print $3, $4}'
	done | ./loadavg ${args[@]} -T "$(iostat_x | awk '{print $1}') Read-Write" \
			-l 'kB_read/s' -l 'kB_wrtn/s' --ylabel 'Rate'
fi

echo "Byebye"
