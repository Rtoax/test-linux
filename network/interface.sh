#!/bin/bash
set -e

interfaces=( $(ls /sys/class/net/) )
declare -a operstates carriers rx_queues tx_queues
verbose=${V}

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
	nr_rx_queues=$(echo "/sys/class/net/${i}/queues/rx-[0-9]*" 2>/dev/null | wc -l || true)
	nr_tx_queues=$(echo "/sys/class/net/${i}/queues/tx-[0-9]*" 2>/dev/null | wc -l || true)

	[[ -z $operstate ]] && operstate=Unknown
	[[ -z $carrier ]] && carrier=Unknown

	operstates+=( ${operstate} )
	carriers+=( ${carrier} )
	rx_queues+=( ${nr_rx_queues} )
	tx_queues+=( ${nr_tx_queues} )
done

# Print interface informations
printf "%-16s %-8s %-8s %-16s %-8s %-8s\n" INTERFACE STATE CARRIER SPEED RX_QUEUE TX_QUEUE
for ((i = 0; i < ${#interfaces[@]}; i++))
do
	speed=$(getifspeed ${interfaces[$i]})
	[[ -z ${speed} ]] && speed=Unknown

	printf "%-16s %-8s %-8s %-16s %-8d %-8d\n" \
		${interfaces[$i]} \
		${operstates[$i]} \
		${carriers[$i]} \
		${speed} \
		${rx_queues[$i]} \
		${tx_queues[$i]}
	[[ ${verbose} ]] && sudo udevadm info /sys/class/net/${interfaces[$i]} | sed 's/^/\t/g'
done

echo
sudo lshw -c network -businfo

echo
sudo ip -br link show up
