#!/bin/bash

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
	grep Huge /proc/meminfo
}

if [[ $(uname -m) == x86_64 ]]; then
	check_x86_64
fi
info
