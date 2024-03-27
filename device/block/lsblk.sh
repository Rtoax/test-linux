#!/bin/bash
blks=( $(ls /sys/block/) )

rota_s()
{
	case $1 in
	0) echo SSD ;;
	1) echo HDD ;;
	esac
}

sched_s()
{
	local l="$@"
	local a=${l##*[}
	local b=${a%]*}
	echo ${b}
}

# or lsblk -o name,rota,sched
printf "%-16s %-8s %-8s\n" "NAME" "ROTA" "SCHED"
for b in ${blks[@]}
do
	rota=$(cat /sys/block/${b}/queue/rotational)
	sched=$(cat /sys/block/${b}/queue/scheduler 2>/dev/null || echo -[-]-)
	printf "%-16s %-8s %-8s\n" \
		${b} \
		$(rota_s ${rota}) \
		$(sched_s ${sched})
done
