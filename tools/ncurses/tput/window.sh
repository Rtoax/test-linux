#!/bin/bash
set -e

cleanup() {
	tput cnorm
	tput init
	clear
	exit 0
}
trap cleanup INT TERM EXIT

tput smcup
tput init
tput civis # hidden curse

for i in $(seq 1 10); do
	read load1 load5 load15 _ < /proc/loadavg
	clear
	tput cup 10 10
	printf "%s,%s,%s\n" ${load1} ${load5} ${load15}
	cat /etc/os-release

	sleep .05
done

tput cnorm
tput rmcup
