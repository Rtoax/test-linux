#!/bin/bash

types=(bios system baseboard chassis processor memory cache connector slot)

for t in ${types[@]}
do
	printf "%-32s %s\n" $t "$(sudo dmidecode -t $t)"
done
