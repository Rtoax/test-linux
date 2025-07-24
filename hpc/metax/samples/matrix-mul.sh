#!/bin/bash
set -e

readonly loop=10000
program=matrix-mul
gpu=0

__usage__()
{
	echo -e "
matrix-mul.sh

-g, --gpu [GPU]        running on GPU
-p, --prog [PROG]      set ELF program
-h, --help             show help info
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options g:p:h \
	--long gpu: \
	--long prog: \
	--long help \
	--name $0 -- "$@")

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
for m in $(seq 10 10 1000)
do
	if [[ $m -eq 10 ]]; then
		verbose=-v
	else
		verbose=""
	fi
	./${program} -m${m} -n${m} -N${loop} -i2 ${verbose} --gpu ${gpu} | tee --append ${program}.log
done
