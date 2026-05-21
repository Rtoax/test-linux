#!/bin/bash
# Copyright (C) 2026 Rong Tao
#
# ttyplot (https://github.com/tenox7/ttyplot)
#   Note: ttyplot only support two lines
#   while sleep 1; do
#     awk '{print $1, $2}' /proc/loadavg
#   done | ttyplot -t "Load Averages (1m, 5m)" -u "load" -2
set -e

readonly C_COL='│'
readonly C_COR='└'
readonly C_ROW='─'
readonly C_UP='▲'
readonly C_RIGHT='►'

readonly old_tty=$(stty -g)

declare -a load1 load5 load15
declare MAX_LOAD_SCALE=0

WINROWS=$(tput lines)
WINCOLS=$(tput cols)
WINBND=5
MAXHIGH=$((WINROWS - WINBND * 2))
MAXWIDTH=$((WINCOLS - WINBND * 2))

cleanup() {
	tput cnorm
	clear
	stty "$old_tty"
	exit 0
}

# window print at location
# $1: row
# $2: col
# $3: string to display
wprint() {
	tput cup $1 $2
	shift 2
	printf "%s" "${*}"
}

print_axis() {
	local i
	for ((i = ${WINBND}; i < $((WINCOLS - WINBND)); i++))
	do
		wprint $((WINROWS - WINBND)) ${i} ${C_ROW}
	done
	wprint $((WINROWS - WINBND)) ${i} ${C_RIGHT}
	wprint $((WINROWS - WINBND + 1)) $((${i} - 5)) "Time"
	wprint $((WINROWS - WINBND)) ${WINBND} ${C_COR}
	wprint $((WINROWS - WINBND + 1)) $((${WINBND} - 1)) "0"
	for ((i = ${WINBND}; i < $((WINROWS - WINBND)); i++))
	do
		wprint ${i} ${WINBND} ${C_COL}
	done
	wprint ${WINBND} ${WINBND} ${C_UP}
	wprint $((${WINBND} - 1)) ${WINBND} "Load Avg"
}

on_winch() {
	clear
	WINROWS=$(tput lines)
	WINCOLS=$(tput cols)
	MAXHIGH=$((WINROWS - WINBND * 2))
	MAXWIDTH=$((WINCOLS - WINBND * 2))
	print_axis
}

scale_val() {
	echo "scale=0; 1000.0 * ${1}" | bc | cut -d. -f1
}

getchar() {
	local key=$(dd bs=1 count=1 2>/dev/null)
	if [[ -n "$key" ]]; then
		printf "%d" "'$key"
	fi
}

# __main__
trap cleanup INT TERM EXIT
trap on_winch WINCH

clear
tput init
tput civis

# Turn off line buffer, no echo for screen.
stty -icanon min 0 time 0 -echo

print_axis

while true; do
	read l1 l5 l15 _ < /proc/loadavg
	load1+=( ${l1} )
	load5+=( ${l5} )
	load15+=( ${l15} )

	wprint 10 10 "$(scale_val ${l1})"
	wprint 12 10 "$(scale_val ${l5})"
	wprint 14 10 "$(scale_val ${l15})"

	key_ascii=$(getchar)
	if [[ -z ${key_ascii} ]]; then
		key_ascii="---"
	fi
	wprint ${WINROWS} 1 "loadavg: ${l1} ${l5} ${l15}, winsize ${WINROWS}x${WINCOLS}, key ${key_ascii}"

	sleep 1
done
