#!/bin/bash
set -e

readonly PROG=$0
readonly loop=10000
program=matrix-mul
gpu=0
max_size=1000
sz_interval=10

__usage__()
{
	echo -en "NAME
	${PROG} - Test matrix mul on GPU or CPU

SYNOPSIS
	${PROG} [-g <IDX>] [...]

ARGUMENTS
	-g, --gpu [GPU]        running on GPU
	-p, --prog [PROG]      set ELF program
	-s, --size [NUM]       set matrix max size, default: ${max_size}
	-i, --interval [NUM]   set matrix size interval, default: ${sz_interval}
	-h, --help             show help info

EXAMPLES
	$ ${PROG} -s 5000 -i 50
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options g:p:s:i:h \
	--long gpu: \
	--long prog: \
	--long size: \
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
	-s | --size)
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
for m in $(seq 10 ${sz_interval} ${max_size})
do
	if [[ $m -eq 10 ]]; then
		verbose=-v
	else
		verbose=""
	fi
	./${program} -m${m} -n${m} -N${loop} -i2 ${verbose} --gpu ${gpu} ${@} | tee --append ${program}.log
done
