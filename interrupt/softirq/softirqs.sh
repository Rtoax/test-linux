#!/bin/bash

declare -a softirqs
softirq_type=

case $1 in
HI | TIMER | NET_TX | NET_RX | BLOCK | IRQ_POLL | TASKLET | SCHED | HRTIMER | RCU)
	softirq_type=$1
	softirqs=( $(cat /proc/softirqs | grep $softirq_type -w) )
	;;
*)
	echo "
 softirqs [type]

 type: HI | TIMER | NET_TX | NET_RX | BLOCK | IRQ_POLL | TASKLET | SCHED | HRTIMER | RCU
"
	exit
	;;
esac


interval=5

echo "Show softirqs: $softirq_type"
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
