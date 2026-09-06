#!/bin/bash

for v in /sys/devices/system/cpu/vulnerabilities/[a-z]*
do
	echo -e "\033[1;32m $(basename $v) \033[m"
	cat $v | sed 's/^/\t/g'
done
