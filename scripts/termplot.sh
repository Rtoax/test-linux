#!/bin/bash
# Copyright (C) 2025 Rong Tao. All rights reserved.
set -e
readonly TERM_HEIGHT=$(( $(stty size | awk '{print $1}') - 10 ))
readonly TERM_WIDTH=$(( $(stty size | awk '{print $2}') - 10 ))

readonly B1='┌'
readonly B2='│'
readonly B3='├'
readonly B4='└'
readonly B5='┼'
readonly B6='┤'
readonly B7='┘'
readonly B8='─'
readonly B9='▲'
readonly B10='▼'
readonly B11='◀'
readonly B12='►'

gotoxy() {
	local x=$2 y=$1
	printf "\033[%d;%df" ${y} ${x}
}

# $1 - x start
# $2 - x end
# $3 - y start
# $4 - y end
# $5 - with arrow or not
drawline() {
	local ix xstart xend
	local iy ystart yend
	local arrow
	local seq_args

	xstart=$1
	xend=$2
	ystart=$3
	yend=$4
	arrow=$5

	if [[ ${xstart} -eq ${xend} ]]; then
		echo "TODO"
	elif [[ ${ystart} -eq ${yend} ]]; then
		if [[ $xstart -lt $xend ]]; then
			seq_args="$xstart 1 $xend"
			[[ ${arrow} ]] && arrow=${B12}
		else
			seq_args="$xstart -1 $xend"
			[[ ${arrow} ]] && arrow=${B11}
		fi

		for ix in $(seq $seq_args)
		do
			gotoxy $ystart $ix
			printf "%s" ${B8}
		done
		printf "%s" ${arrow}
	else
		echo >&2 "ERROR: invalid parameter"
		exit 1
	fi
}

# $1 - x start
# $2 - x end
# $3 - y
# $4 - with arrow or not
horizontal_line() {
	drawline $1 $2 $3 $3 $4
}

# $1 - x
# $2 - y
# $3 - length
# $4 - with arrow or not
#vertical_line() {
#}

clear
horizontal_line 4 $((${TERM_WIDTH} - 4)) ${TERM_HEIGHT} YES
echo
