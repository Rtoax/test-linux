#!/bin/bash
# Copyright (C) 2026 Rong Tao
#
# ttyplot (https://github.com/tenox7/ttyplot)
#   Note: ttyplot only support two lines
#   while sleep 1; do
#     awk '{print $1, $2}' /proc/loadavg
#   done | ttyplot -t "Load Averages (1m, 5m)" -u "load" -2
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
readonly K_ENTER=10

readonly old_tty=$(stty -g)

declare -a load1 load5 load15

WINROWS=$(tput lines)
WINCOLS=$(tput cols)
WINBND=5
MAXHIGH=$((WINROWS - WINBND * 2 - 1))
MAXWIDTH=$((WINCOLS - WINBND * 2 - 2))

cleanup() {
	local ret=$?
	echo "exit with ${ret}"
	tput cnorm
	stty "$old_tty"
	exec 2>&-
	clear
	exit ${ret}
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
		printf "\033[1;7;31m%s\033[m" "${*}"
		;;
	yellow)
		shift
		printf "\033[1;7;33m%s\033[m" "${*}"
		;;
	blue)
		shift
		printf "\033[1;7;34m%s\033[m" "${*}"
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
	for load in ${load1[@]} ${load5[@]} ${load15[@]}
	do
		local scale=$(scale_val ${load})
		if [[ ${MAX_LOAD_SCALE} -lt ${scale} ]]; then
			MAX_LOAD_SCALE=${scale}
		fi
	done
}

declare -a prev_cols prev_raws
__print_load() {
	local color=$1
	shift
	local loads=( ${@} )
	# Print loads
	local nloads=${#loads[@]}
	for ((i = 0; i < ${nloads}; i++))
	do
		local col=$((WINBND + 1 + MAXWIDTH - ${nloads} + i))
		local row_scale=$(scale_val ${loads[i]})
		local row=$(( MAXHIGH + WINBND - row_scale * MAXHIGH / ${MAX_LOAD_SCALE} + WINBND ))
		prev_cols+=( ${col} )
		prev_rows+=( ${row} )
		# wprint 2 1 "${col} ${row} ${nloads}"
		wprint ${row} ${col} ${color} "${C_ROW}"
	done
}
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

	__print_load red ${load1[@]}
	__print_load yellow ${load5[@]}
	__print_load blue ${load15[@]}
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

	# Remove index 0 if beyond boundary
	if [[ ${#load1[@]} -ge ${MAXWIDTH} ]]; then
		load1=( ${load1[@]:1} )
		MAX_LOAD_SCALE=0
	fi
	if [[ ${#load5[@]} -ge ${MAXWIDTH} ]]; then
		load5=( ${load5[@]:1} )
		MAX_LOAD_SCALE=0
	fi
	if [[ ${#load15[@]} -ge ${MAXWIDTH} ]]; then
		load15=( ${load15[@]:1} )
		MAX_LOAD_SCALE=0
	fi
	getmaxload

	print_load

	wprint 1 1 "load1 scale $(scale_val ${l1}), max = ${MAX_LOAD_SCALE}"
	wprint 2 1 "load5 scale $(scale_val ${l5})"
	wprint 3 1 "load15 scale $(scale_val ${l15})"

	key_ascii=$(getchar)
	if [[ -z ${key_ascii} ]]; then
		key_ascii="---"
	fi
	wprint $((WINROWS - 4)) 1 red "load1 ${l1}"
	wprint $((WINROWS - 3)) 1 yellow "load5 ${l5}"
	wprint $((WINROWS - 2)) 1 blue "load15 ${l15}"
	wprint ${WINROWS} 1 "winsize ${WINROWS}x${WINCOLS}, key ${key_ascii}, nload ${#load1[@]}"

	sleep 1
done
