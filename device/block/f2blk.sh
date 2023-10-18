#!/bin/bash
set -e

find_file_block() {
	local file major minor block

	file=$1
	major=$( stat --printf="%Hd" ${file} )
	minor=$( stat --printf="%Ld" ${file} )
	# /dev/block/major:minor or /sys/dev/block/major:minor
	block=$( basename $(readlink /dev/block/${major}\:${minor}) )
	echo ${block}
}

files=(
	/
	/home
	/etc/os-release
	/boot/vmlinuz-$(uname -r)
)
for f in ${files[@]}
do
	printf "%-16s %s\n" $( find_file_block ${f} ) ${f}
done
