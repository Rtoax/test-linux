#!/bin/bash
# Copyright 2023 Rong Tao.
#
# Print softirqs
#
set -e

declare -a softirqs
softirq_type=
interval=5
color=YES

__usage__()
{
	echo "
 softirqs [args]

 -t, --type       HI | TIMER | NET_TX | NET_RX | BLOCK | IRQ_POLL | TASKLET | SCHED | HRTIMER | RCU

 --no-color       no highlight color

 -h, --help       show this information
"
	exit ${1-0}
}

ARGS=$(getopt \
	--options t:h \
	--long type: \
	--long no-color \
	--long help \
	-n softirqs -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$ARGS"

while true; do
	case $1 in
	-t | --type)
		shift
		case $1 in
		HI | TIMER | NET_TX | NET_RX | BLOCK | IRQ_POLL | TASKLET | SCHED | HRTIMER | RCU)
			softirq_type=$1
			;;
		*)
			echo "ERROR: Unknow softirq, check -h,--help"
			exit 1
		esac
		shift
		;;
	--no-color)
		shift
		color=""
		;;
	-h | --help)
		shift
		__usage__
		;;
	--)
		shift
		break
		;;
	esac
done

[[ -z ${softirq_type} ]] && echo "ERROR: Must specify type. see -h" && exit 1

update_softirqs()
{
	softirqs=( $(cat /proc/softirqs | grep $softirq_type -w) )
	# echo ${softirqs[@]}
	# Remove type label like 'SCHED:'
	unset softirqs[0]
	# echo ${softirqs[@]}
}

print_softirqs()
{
	echo
	echo "Printing /proc/softirqs, print with alignment"
	echo "Show softirqs: $softirq_type, number ${#softirqs[@]}"
	echo
	[[ ! -z ${color} ]] && echo -e -n "\033[1m"
	for ((i = 0; i < $interval - 1; i++))
	do
		printf "%-4s %-16s\t" CPU NUM
	done
	printf "%-4s %-16s\n" CPU NUM
	[[ ! -z ${color} ]] && echo -e -n "\033[m"


	for ((i = 0; i < ${#softirqs[@]}; i+=$interval))
	do
		for ((j = 0; j < $interval - 1; j++))
		do
			# +1: skip softirqs[0]
			printf "%-4d %-16d\t" $( expr $i + $j ) ${softirqs[$i + $j + 1]}
		done
		printf "%-4d %-16d\n" $( expr $i + $j ) ${softirqs[$i + $j + 1]}
	done
}

update_softirqs
print_softirqs
