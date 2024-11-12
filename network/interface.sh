#!/bin/bash
set -e

interfaces=( $(ls /sys/class/net/) )
declare -a operstates carriers

getifspeed()
{
	local iface=$1
	( ethtool $iface 2>/dev/null || echo "Speed Unknown" ) | grep Speed | awk '{print $2}'
}

# Get informations
for i in ${interfaces[@]}
do
	operstate=$(cat /sys/class/net/${i}/operstate 2>/dev/null || true)
	carrier=$(cat /sys/class/net/${i}/carrier 2>/dev/null || true)

	[[ -z $operstate ]] && operstate=Unknown
	[[ -z $carrier ]] && carrier=Unknown

	operstates+=( ${operstate} )
	carriers+=( ${carrier} )
done

# Print interface informations
printf "%-16s %-8s %-8s %-8s\n" INTERFACE STATE CARRIER SPEED
for ((i = 0; i < ${#interfaces[@]}; i++))
do
	printf "%-16s %-8s %-8s %-8s\n" \
		${interfaces[$i]} \
		${operstates[$i]} \
		${carriers[$i]} \
		$(getifspeed ${interfaces[$i]})
	sudo udevadm info /sys/class/net/${interfaces[$i]} | sed 's/^/\t/g'
done

echo
sudo lshw -c network -businfo

echo
sudo ip -br link show up
