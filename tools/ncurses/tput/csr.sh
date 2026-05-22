#!/bin/bash
# csr: Change Scrolling Region
set -e

tput smcup
tput init
tput civis

tput csr 0 10


for i in $(seq 1 20); do
	# tput ri # Scrolling up
	tput ind # Scrolling down
	printf "Hello World ${i}"
	sleep .05
done

tput cnorm
tput rmcup
