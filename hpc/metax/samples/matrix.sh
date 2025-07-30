#!/bin/bash
set -e

readonly PROG=$0
readonly loop=10000
program=matrix
gpu=0
max_size=10000
sz_start=100
sz_interval=50

__usage__()
{
	echo -en "NAME
	${PROG} - Test matrix mul on GPU or CPU

SYNOPSIS
	${PROG} [-g <IDX>] [...]

ARGUMENTS
	-g, --gpu [GPU]        running on GPU
	-p, --prog [PROG]      set ELF program
	-s, --start [NUM]      set matrix size start, default: ${sz_start}
	-M, --max [NUM]        set matrix max size, default: ${max_size}
	-i, --interval [NUM]   set matrix size interval, default: ${sz_interval}
	-h, --help             show help info

EXAMPLES
	$ ${PROG} -s 5000 -i 50 -- --vector
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options g:p:s:M:i:h \
	--long gpu: \
	--long prog: \
	--long start: \
	--long max: \
	--long interval: \
	--long help \
	--name ${PROG} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"
while true; do
	case $1 in
	-g | --gpu)
		shift
		gpu=$1
		shift
		;;
	-p | --prog)
		shift
		program=$1
		shift
		;;
	-s | --start)
		shift
		sz_start=$1
		shift
		;;
	-M | --max)
		shift
		max_size=$1
		shift
		;;
	-i | --interval)
		shift
		sz_interval=$1
		shift
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

rm -f ${program}.log
for m in $(seq ${sz_start} ${sz_interval} ${max_size})
do
	if [[ $m -eq ${sz_start} ]]; then
		verbose=-v
	else
		verbose=""
	fi
	./${program} -m${m} -n${m} -N${loop} -i2 ${verbose} --gpu ${gpu} ${@} | tee --append ${program}.log
done
