#!/bin/bash

timestamps=( $(tcpdump -tt -r a.pcap |awk  '{print $1}' |awk -F. '{print $1$2}') )

for ((i = 1; i < ${#timestamps[@]}; i++))
do
	i_prev=$(( $i - 1 ))
	diff=$(( ${timestamps[$i]} - ${timestamps[$i_prev]} ))
	printf "%s\n" $diff
done
