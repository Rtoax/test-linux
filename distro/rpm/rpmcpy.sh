#!/bin/bash
#
# Copy rpms command with all depends
#
# Copyright (C) 2022-2026 Rong Tao.
#
set -e

get_pkg_deps()
{
	deps=$(rpm -q --requires "$@" | while read req ver; do
		p=$(rpm -q --whatprovides "$req")
		[ $? -eq 0 ] && echo $p
	done | sort -u)
	echo "$@ $deps"
}

rpm_requires()
{
	packages=$(get_pkg_deps util-linux tcpdump ethtool iputils iproute)
	for p in $packages; do
		rpm -ql $p | grep -E -v "(/man/)|(/bash-completion/)|(/doc/)" | sed -e 's/\n/ /g'
	done | sort -u
}

root_dir=$PWD/initrd-tmp-dir.out

copy_files_from_host()
{
	for i in $(rpm_requires)
	do
		# SKip directory
		test -d $i && continue

		dir=$(dirname $i)
		file=$(basename $i)

		dst_dir=$root_dir/$dir

		test ! -d $dst_dir && sudo mkdir -p $dst_dir

		test -e $dst_dir/$file && \
			echo "Exist $dst_dir/$file" && \
			continue

		sudo cp $i $dst_dir
		echo "COPY $i"
	done
}

mkdir $root_dir

copy_files_from_host
