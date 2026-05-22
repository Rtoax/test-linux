#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2026 Rong Tao
#
# Plot and display a loadavg graph of 1, 5, 15 minutes in the Linux terminal
# with minimal dependencies.
#
# ttyplot (https://github.com/tenox7/ttyplot)
#   Note: ttyplot only support two lines
#   while sleep 1; do
#     awk '{print $1, $2}' /proc/loadavg
#   done | ttyplot -t "Load Averages (1m, 5m)" -u "load" -2
#
# TODO: `while :; do tput; print; done` mode is too slow, we should use pure C.
# see also tools/ncurses/loadavg.c.
set -e

if [[ ${VERBOSE} ]]; then
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
fi

exec 2<> $PWD/loadavg.stderr.log

readonly C_COL='│'
readonly C_COR='└'
readonly C_ROW='─'
readonly C_UP='▲'
readonly C_RIGHT='►'
readonly C_ASCII220='▄'
readonly K_ENTER=10

readonly old_tty=$(stty -g)

declare -a load1 load5 load15
declare -a load1_scale load5_scale load15_scale

DATEBASE=loadavg.db
WINROWS=
WINCOLS=
readonly WINBND=6
MAXHIGH=
MAXWIDTH=

init_panel() {
	WINROWS=$(tput lines)
	WINCOLS=$(tput cols)
	MAXHIGH=$((WINROWS - WINBND * 2 - 1))
	MAXWIDTH=$((WINCOLS - WINBND * 2 - 2))
}

cleanup() {
	local ret=$?
	echo "exit with ${ret}"
	tput cnorm
	tput rmcup
	stty "$old_tty"
	exec 2>&-
	exit ${ret}
}

# window print at location
# $1: row
# $2: col
# $3: [optional] format of color, bold, clean, etc.
# left args: string to display
#   $4: if $3=clean, $4 is size of clean
wprint() {
	tput cup $1 $2
	shift 2
	case $1 in
	red)
		shift
		printf "\033[1;31m%s\033[m" "${*}"
		;;
	yellow)
		shift
		printf "\033[1;33m%s\033[m" "${*}"
		;;
	blue)
		shift
		printf "\033[1;34m%s\033[m" "${*}"
		;;
	clean)
		shift
		printf "%*s" $1 " "
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
	init_panel
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
	local scale
	for scale in ${load1_scale[@]} ${load5_scale[@]} ${load15_scale[@]}
	do
		if [[ ${MAX_LOAD_SCALE} -lt ${scale} ]]; then
			MAX_LOAD_SCALE=${scale}
		fi
	done
}

declare -a prev_cols prev_raws
declare -A last_row # array[red|yellow|blue]=row
__print_load_scale() {
	local color=$1
	shift
	local i col row
	local loads_scale=( ${@} )
	# Print loads_scale
	local nloads=${#loads_scale[@]}
	for ((i = 0; i < ${nloads}; i++))
	do
		col=$((WINBND + 2 + MAXWIDTH - ${nloads} + i))
		local row_scale=${loads_scale[i]}
		row=$(( MAXHIGH + WINBND - row_scale * MAXHIGH / ${MAX_LOAD_SCALE} ))
		prev_cols+=( ${col} )
		prev_rows+=( ${row} )
		# wprint 2 1 "${col} ${row} ${nloads}"
		wprint ${row} ${col} ${color} "${C_ASCII220}"
	done

	# record Y axis in the end, and record it for refresh.
	last_row[$color]=${row}
}
__clean_load() {
	local i

	# reset previous first
	for ((i = 0; i < ${#prev_cols[@]}; i++))
	do
		# wprint 1 1 "${#prev_rows[@]}, ${#prev_cols[@]}"
		wprint ${prev_rows[i]} ${prev_cols[i]} clean 1
	done
	unset prev_cols
	unset prev_rows
}
print_load() {
	__clean_load

	__print_load_scale red ${load1_scale[@]}
	__print_load_scale yellow ${load5_scale[@]}
	__print_load_scale blue ${load15_scale[@]}

	# Print Y axis values, and record it for refresh and cleanup.
	local last_load1="${load1[-1]}"
	local last_load5="${load5[-1]}"
	local last_load15="${load15[-1]}"
	wprint ${last_row[red]} 0 red "${last_load1}"
	wprint ${last_row[yellow]} 0 yellow "${last_load5}"
	wprint ${last_row[blue]} 0 blue "${last_load15}"

	local i
	for ((i = 0; i < ${#last_load1}; i++)); do
		prev_cols+=( ${i} )
		prev_rows+=( ${last_row[red]} )
	done
	for ((i = 0; i < ${#last_load5}; i++)); do
		prev_cols+=( ${i} )
		prev_rows+=( ${last_row[yellow]} )
	done
	for ((i = 0; i < ${#last_load15}; i++)); do
		prev_cols+=( ${i} )
		prev_rows+=( ${last_row[blue]} )
	done
}

# __main__
trap cleanup INT TERM EXIT
trap on_winch WINCH

tput smcup
tput init
tput civis

rm -f ${DATEBASE}

# Turn off line buffer, no echo for screen.
stty -icanon min 0 time 0 -echo

init_panel

print_axis

while true; do
	read l1 l5 l15 _ < /proc/loadavg
	load1+=( ${l1} )
	load5+=( ${l5} )
	load15+=( ${l15} )

	l1_scale=$(scale_val ${l1})
	l5_scale=$(scale_val ${l5})
	l15_scale=$(scale_val ${l15})

	load1_scale+=( ${l1_scale} )
	load5_scale+=( ${l5_scale} )
	load15_scale+=( ${l15_scale} )

	echo -e "${l1}\t${l5}\t${l15}\t$(date -u +%s)" >> ${DATEBASE}

	# Remove index 0 if beyond boundary
	nload=${#load1[@]}
	if [[ ${nload} -ge ${MAXWIDTH} ]]; then
		x=$((nload - MAXWIDTH))
		load1=( ${load1[@]:${x}} )
		load5=( ${load5[@]:${x}} )
		load15=( ${load15[@]:${x}} )
		load1_scale=( ${load1_scale[@]:${x}} )
		load5_scale=( ${load5_scale[@]:${x}} )
		load15_scale=( ${load15_scale[@]:${x}} )
		MAX_LOAD_SCALE=0
	fi

	getmaxload

	print_load

	key_ascii=$(getchar)
	[[ -z ${key_ascii} ]] && key_ascii="---"
	[[ ${key_ascii} == 113 ]] && exit 0

	wprint $((WINROWS - 4)) 1 red "load1 ${l1}, scale ${l1_scale}, max = ${MAX_LOAD_SCALE}"
	wprint $((WINROWS - 3)) 1 yellow "load5 ${l5}, scale ${l5_scale}"
	wprint $((WINROWS - 2)) 1 blue "load15 ${l15}, scale ${l15_scale}"
	wprint ${WINROWS} 1 "winsize ${WINROWS}x${WINCOLS}, key ${key_ascii}, nload ${#load1[@]}"

	sleep 1
done
