#!/bin/bash

cpu_freq()
{
	cat /proc/cpuinfo | grep cpu | grep  MHz | sed -e 's/.*:[^0-9]//'
}


cpu_stat()
{
	local i item
	local proc="/proc/stat"
	declare -a _cpus
	declare -a users nices systems idles iowaits irqs softirqs steals guests guest_nices

	i=0
	cat /proc/stat | grep ^cpu | while read line
	do
		items=( $line )
		_cpus+=( ${items[0]} )
		users+=( ${items[1]} )
		nices+=( ${items[2]} )
		systems+=( ${items[3]} )
		idles+=( ${items[4]} )
		iowaits+=( ${items[5]} )
		irqs+=( ${items[6]} )
		softirqs+=( ${items[7]} )
		steals+=( ${items[8]} )
		guests+=( ${items[9]} )
		guest_nices+=( ${items[10]} )

		printf "%-8s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n" \
			${_cpus[$i]} \
			${users[$i]} \
			${nices[$i]} \
			${systems[$i]} \
			${idles[$i]} \
			${iowaits[$i]} \
			${irqs[$i]} \
			${softirqs[$i]} \
			${steals[$i]} \
			${guests[$i]} \
			${guest_nices[$i]}
		(( i++ ))
	done
}

cpu_stat
iostat -c
mpstat -P ALL

