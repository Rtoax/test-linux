#!/bin/bash
set -e

check_x86_64()
{
	# Support 2M pages
	if [[ $(lscpu | grep -w --only-matching pse) ]]; then
		echo Support 2M hugepage
	fi
	# Support 1G pages
	if [[ $(lscpu | grep -w --only-matching pdpe1gb) ]]; then
		echo Support 1G hugepage
	fi

}

info() {
	grep ^Huge /proc/meminfo
	sysctl vm.nr_hugepages
	# Write like:
	# echo "256" | sudo tee /proc/sys/vm/nr_hugepages
	sudo cat /proc/sys/vm/nr_hugepages
	echo "PAGE_SIZE = $(getconf PAGE_SIZE)"
	ls /sys/kernel/mm/hugepages/
}

if [[ $(uname -m) == x86_64 ]]; then
	check_x86_64
fi

info
