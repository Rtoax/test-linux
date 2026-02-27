#!/bin/bash
# This script only display kernel version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e

readonly FULL=$(uname -r)

case $1 in
short)
	echo ${FULL} | grep -Eo '^[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
	;;
full)
	echo ${FULL}
	;;
*)
	echo >&2 "Usage: kversion.sh [short|full]"
	exit 1
	;;
esac
