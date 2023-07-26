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

path2inode "$@"

