#!/bin/bash
set -e

# TODO
while sleep 1; do
	loads=( $(mpstat -P ALL | awk '{print $NF}' | grep -E '[0-9]+\.[0-9]+') )
	echo ${loads[@]}
done | ../loadavg --title 'CPU Loads' --ylabel '%idle'
