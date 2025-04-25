#!/bin/bash
set -e

readonly GIT_TOPDIR=$(git rev-parse --show-toplevel 2>/dev/null || :)

remove_broken_symlinks()
{
	sudo find ${GIT_TOPDIR} -type l -xtype l -delete
}

bad_way()
{
	local f
	local symlinks=( $(find ${GIT_TOPDIR} -path ".git" -a -prune -o -type l -exec echo {} +) )
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
	local broken_symlinks=( $(find ${GIT_TOPDIR} -xtype l) )
	for f in ${broken_symlinks[@]}
	do
		echo "Broken-symlink: ${f}"
	done
}

good_way
