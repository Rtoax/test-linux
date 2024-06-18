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
