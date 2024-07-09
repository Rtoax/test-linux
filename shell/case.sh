#!/bin/bash

yes_or_no()
{
	case $1 in
	[Nn]|[Nn][On])
		echo No
		;;
	[Yy]|[Yy][Ee]|[Yy][Ee][Ss])
		echo Yes
		;;
	*)
		echo "$0 [Yes|No]"
		;;
	esac
}

yes_or_no "$@"

usage_1()
{
	case $1 in
	# Not support this synax
	--{help,usage})
		echo "Usage"
		;;
	esac
}

# Print nothing
usage_1 --help
