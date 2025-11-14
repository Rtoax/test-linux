#!/bin/bash
# Copyright (c) 2022-2025 Rong Tao
set -e

readonly ROOT_DIRECTORY=$(dirname $(realpath $0)/../)

remove_broken_symlinks()
{
	find ${TEST_LINUX_ROOT_DIR} -type l -xtype l -delete
}

bad_way()
{
	local f
	local symlinks=( $(find ${TEST_LINUX_ROOT_DIR} -path ".git" -a -prune -o -type l -exec echo {} +) )
	for f in ${symlinks[@]}
	do
		real_f=$(realpath $f 2>/dev/null || true)
		if [[ ! -f $real_f ]] && [[ ! -d $real_f ]]; then
			echo "Broken-symlink: $f"
		fi
	done
}

good_way()
{
	local f
	local broken_symlinks=( $(find ${TEST_LINUX_ROOT_DIR} -xtype l) )
	for f in ${broken_symlinks[@]}
	do
		echo "Broken-symlink: ${f}"
	done
}

good_way
