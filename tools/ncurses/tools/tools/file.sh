#!/bin/bash
# display files opened
set -e

while true; do
	awk '{print $1}' /proc/sys/fs/file-nr
	sleep 1
done | ../plotcake ${args[@]} --title 'File Number' -l 'opened' -o file ${@}
