#!/bin/bash
blks=( $(ls /sys/block/) )

rota_s()
{
	case $1 in
	0) echo SSD ;;
	1) echo HDD ;;
	esac
}

# or lsblk -o name,rota
printf "%-16s %-8s\n" "BLK" "TYPE"
echo "--------------------"
for b in ${blks[@]}
do
	rota=$(cat /sys/block/${b}/queue/rotational)
	printf "%-16s %-8s\n" ${b} $(rota_s ${rota})
done
