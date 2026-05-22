#!/bin/bash
set -e

cleanup() {
	tput cnorm
	tput init
	clear
	exit 0
}
trap cleanup INT TERM EXIT

clear
tput init
tput civis # hidden curse
tput smcup # swap to a clean screen

for i in $(seq 1 10); do
	read load1 load5 load15 _ < /proc/loadavg
	clear
	tput cup 10 10
	printf "%s,%s,%s" ${load1} ${load5} ${load15}

	sleep .01
done

tput rmcup # turn off screen, back to main screen
