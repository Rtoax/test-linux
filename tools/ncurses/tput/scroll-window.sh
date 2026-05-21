#!/bin/bash
set -e

cleanup() {
	tput cnorm
	clear
	exit 0
}
trap cleanup INT TERM EXIT

clear
tput civis

for i in $(seq 1 10); do
	read load1 load5 load15 _ < /proc/loadavg
	clear
	tput cup 10 10
	printf "%s,%s,%s" ${load1} ${load5} ${load15}

	sleep .01
done
