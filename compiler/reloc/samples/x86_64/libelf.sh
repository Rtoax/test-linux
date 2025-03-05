#!/bin/bash
set -e

sym2sec() {
	local elf=$1
	local fun=$2
	readelf --syms --wide ${elf} | grep -w ${fun} | awk '{print $(NF-1)}'
}

sym2value() {
	local elf=$1
	local fun=$2
	readelf --syms --wide ${elf} | grep -w ${fun} | awk '{print "0x"$2}'
}

name2sec() {
	local elf=$1
	local name=$2
	readelf --sections --wide ${elf} | awk -v name=${name} '
		{
			# [ 1] .text
			if ($3==name) {
				print $2
			}
			# [1] .text
			if ($2==name) {
				print $1
			}
		}' | grep -o [0-9]*
}

sec2name() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print $(NF-9)}'
}

sec2offset() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print "0x"$(NF-6)}'
}

sec2addr() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print "0x"$(NF-7)}'
}
