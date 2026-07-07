#!/bin/bash
set -e

path2inode()
{
	stat --printf='%i\n' "$@"
}

inode2path()
{
	local ino=$1
	# FIXME: change the directory
	sudo find / -xdev -inum ${ino}
}

list_inodes()
{
	sudo find /etc/ -type f -exec stat -c %i {} \;
}

if [[ ${1} ]]; then
	path2inode "${1}"
else
	ino=$(path2inode "/etc/os-release")
	inode2path ${ino}
fi
