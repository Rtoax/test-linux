#!/bin/bash
# This script only display uefi version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: version.sh [--major|--minor]
#
set -e
BPFTRACE=$(which uefi 2>/dev/null || :)
version=$(sudo dmesg | grep -i "EFI v" | grep -Eo 'v[0-9]+\.[0-9]+')

case $1 in
--major)
	echo ${version%%.*} | tr -d v
	;;
--minor)
	echo ${version##*.}
	;;
"")
	echo ${version}
	;;
*)
	exit 1
	;;
esac
