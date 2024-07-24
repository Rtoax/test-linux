#!/bin/bash

path2inode()
{
	stat --printf='%i\n' "$@"
}

inode2path()
{
	local ino=$1
	# FIXME: change the directory
	find / -xdev -inum ${ino}
}

list_inodes()
{
	sudo find /etc/ -type f -exec stat -c %i {} \;
}

path2inode "$@"

