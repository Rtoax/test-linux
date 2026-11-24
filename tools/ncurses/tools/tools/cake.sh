#!/bin/bash
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

height=$(tput lines)
width=$(tput cols)

x10=$( printf "%0.s$((height / 3)) " $(seq 1 $((width / 5))) )
x11=$( printf "%0.s$((height / 3)) " $(seq 1 $((width / 3))) )
x20=$( printf "%0.s$((height / 2)) " $(seq 1 $((width / 3))) )

l1=( 1 ${x10} ${x20} ${x10} 1 )
l2=( 1 ${x10} ${x11} ${x10} 1 )

for ((i = 0;; i++))
do
	echo ${l1[i]} ${l2[i]} ${height}
	sleep 0.01

	# Test enough and exit
	if [[ ${i} -gt ${#l1[@]} ]]; then
		kill -INT 0
	fi
done | ${PLOTCAKE} --title 'Happy Birthday' \
	-L unicode-boldbold -L unicode-boldbold \
	-C w -C w -o cake "${@}"
