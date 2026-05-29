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

while sleep 0.05; do
	seq 1 1 28
done | ./loadavg ${args[@]}

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
	num=( $(ps -e | wc -l)
	      $(ps -eo state | grep ^S | wc -l)
	      $(ps -eo state | grep ^R | wc -l)
	      $(ps -eo state | grep ^I | wc -l) )
	echo ${num[@]}
done | ./loadavg ${args[@]} --title 'Process Number' --xlabel 'Time' --ylabel 'Number' \
		-l All -l Sleep -l Run -l Idle

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

# display files opened
while sleep .3; do
	awk '{print $1}' /proc/sys/fs/file-nr
done | ./loadavg ${args[@]} --title 'File Number' -l 'opened'

# display the NIC rx
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
while sleep 0.1; do
	grep ${maxiface} /proc/net/dev | awk '{print $2, $10}'
done | ./loadavg ${args[@]} --title "${maxiface} tx/rx" -l RX -l TX

echo "Byebye"
