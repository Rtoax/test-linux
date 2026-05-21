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
readonly K_ENTER=10

readonly old_tty=$(stty -g)

declare -a load1 load5 load15

WINROWS=$(tput lines)
WINCOLS=$(tput cols)
WINBND=5
MAXHIGH=$((WINROWS - WINBND * 2 - 1))
MAXWIDTH=$((WINCOLS - WINBND * 2 - 2))

cleanup() {
	tput cnorm
	clear
	stty "$old_tty"
	exit 0
}

# window print at location
# $1: row
# $2: col
# $3: [optional] format of color, bold, etc.
# left args: string to display
wprint() {
	tput cup $1 $2
	shift 2
	case $1 in
	red)
		shift
		printf "\033[1;31m%s\033[m" "${*}"
		;;
	*)
		printf "%s" "${*}"
		;;
	esac
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
	local key ascii
	if read -n1 -s -t 0.01 key 2>/dev/null; then
		ascii=$(printf "%d" "'$key")
		# Get enter
		if [[ -z "$key" ]]; then
			echo ${K_ENTER}
		else
			echo $ascii
		fi
	fi
}

declare MAX_LOAD_SCALE=0
getmaxload() {
	local load
	for load in ${load1[@]}
	do
		local scale=$(scale_val ${load})
		if [[ ${MAX_LOAD_SCALE} -lt ${scale} ]]; then
			MAX_LOAD_SCALE=${scale}
		fi
	done
}

declare -a prev_cols prev_raws
print_load() {
	local i

	# reset previous first
	for ((i = 0; i < ${#prev_cols[@]}; i++))
	do
		# wprint 1 1 "${#prev_rows[@]}, ${#prev_cols[@]}"
		wprint ${prev_rows[i]} ${prev_cols[i]} " "
	done
	unset prev_cols
	unset prev_rows

	# Print new
	local nload1=${#load1[@]}
	for ((i = 0; i < ${nload1}; i++))
	do
		local col=$((WINBND + 1 + MAXWIDTH - ${nload1} + i))
		local row_scale=$(scale_val ${load1[i]})
		local row=$(( MAXHIGH - row_scale * MAXHIGH / 1000 + WINBND + 1 ))
		prev_cols+=( ${col} )
		prev_rows+=( ${row} )
		# wprint 2 1 "${col} ${row} ${nload1}"
		wprint ${row} ${col} red "${C_ROW}"
	done
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

	# Remove index 0, TODO: load5 and load15
	if [[ ${#load1[@]} -ge ${MAXWIDTH} ]]; then
		load1=( ${load1[@]:1} )
		MAX_LOAD_SCALE=0
	fi
	getmaxload

	print_load

	wprint 10 10 "$(scale_val ${l1}), max = ${MAX_LOAD_SCALE}"
	wprint 12 10 "$(scale_val ${l5})"
	wprint 14 10 "$(scale_val ${l15})"

	key_ascii=$(getchar)
	if [[ -z ${key_ascii} ]]; then
		key_ascii="---"
	fi
	wprint ${WINROWS} 1 "loadavg: ${l1} ${l5} ${l15}, winsize ${WINROWS}x${WINCOLS}, key ${key_ascii}, nload ${#load1[@]}"

	sleep 1
done
