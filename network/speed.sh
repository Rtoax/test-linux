#!/bin/bash

ifname=$1

if [[ -z ${ifname} ]]; then
	echo "ERROR: input interface name"
	exit 1
fi

function print_speed()
{
	bytes=$1
	if [[ $bytes -lt 1024 ]]; then
		print_bytes="$bytes B/s"
	elif [[ $bytes -gt 1073741824 ]]; then
		print_bytes=$(echo $bytes | awk '{print $1/1073741824 " GB/s"}')
	elif [[ $bytes -gt 1048576 ]]; then
		print_bytes=$(echo $bytes | awk '{print $1/1048576 " MB/s"}')
	else
		print_bytes=$(echo $bytes | awk '{print $1/1024 " KB/s"}')
	fi
	echo $print_bytes
}

while true
do
	rx_prev=$(cat /proc/net/dev | grep $ifname | sed 's/:/ /g' | awk '{print $2}')
	tx_prev=$(cat /proc/net/dev | grep $ifname | sed 's/:/ /g' | awk '{print $10}')
	sleep 1
	rx_next=$(cat /proc/net/dev | grep $ifname | sed 's/:/ /g' | awk '{print $2}')
	tx_next=$(cat /proc/net/dev | grep $ifname | sed 's/:/ /g' | awk '{print $10}')

	clear
	echo -e "\t RX $(date +%k:%M:%S) TX"

	RX=$((${rx_next} - ${rx_prev}))
	TX=$((${tx_next} - ${tx_prev}))

	echo RX Speed: $(print_speed $RX)
	echo TX Speed: $(print_speed $TX)
done
