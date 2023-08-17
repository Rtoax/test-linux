#!/bin/bash

for i in $(seq 1 10000)
do
	printf "$(date +'%Y/%M/%d %H:%M:%S') %d\n" $i > /dev/tty
	sleep 2
done
