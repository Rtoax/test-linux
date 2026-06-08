#!/bin/bash
# display files opened
set -e

while sleep 1; do
	awk '{print $1}' /proc/sys/fs/file-nr
done | ../plotcake ${args[@]} --title 'File Number' -l 'opened' ${@}
