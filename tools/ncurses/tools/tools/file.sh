#!/bin/bash
# display files opened
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

while true; do
	awk '{print $1}' /proc/sys/fs/file-nr
	sleep 1
done | ${PLOTCAKE} ${args[@]} --title 'File Number' -l 'opened' -o file ${@}
