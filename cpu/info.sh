#!/bin/bash
set -e

cpu_freq()
{
	cat /proc/cpuinfo | grep cpu | grep  MHz | sed -e 's/.*:[^0-9]//'
}

cpu_stat()
{
	local i item
	local proc="/proc/stat"

	local -a _cpus
	local -a users nices systems idles iowaits irqs softirqs steals guests guest_nices

	printf "%-8s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n" \
		CPU USER NICE SYSTEM IDLE IOWAIT IRQ SOFTIRQ STEAL GUEST GUEST_NICE
	i=0
	cat ${proc} | grep ^cpu | while read line
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
		i=$( expr $i + 1 )
	done
}

cpu_stat
iostat -c
mpstat -P ALL

