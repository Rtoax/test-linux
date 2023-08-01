#!/bin/bash

softirqs=( $(cat /proc/softirqs | grep NET_RX) )

interval=5

echo "Show softirqs: NET_RX"
for ((i = 0; i < $interval - 1; i++))
do
printf "%-4s %-16s\t" CPU NUM
done
printf "%-4s %-16s\n" CPU NUM

unset softirqs[0]


for ((i = 0; i < ${#softirqs[@]}; i+=$interval))
do
	for ((j = 0; j < $interval - 1; j++))
	do
		printf "%-4d %-16d\t" $( expr $i + $j ) ${softirqs[$i + $j]}
	done
	printf "%-4d %-16d\n" $( expr $i + $j ) ${softirqs[$i + $j]}
done
