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

height=20
height_start=5
width_start=5
width=$(( ${TERM_WIDTH} - ${width_start} * 2 ))

gotoxy() {
	local x=$2 y=$1
	printf "\033[%d;%df" ${y} ${x}
}

# $1 - x
# $2 - y
# $3 - length
# $4 - with arrow or not
horizontal_line() {
	local ix x y len arrow
	x=$1
	y=$2
	len=$3
	arrow=$4
	for ix in $(seq $x 1 $(($x + $len)))
	do
		gotoxy $y $ix
		printf "%s" ${B8}
	done
	[[ ${arrow} ]] && printf "%s" ${B12}
}

# $1 - x
# $2 - y
# $3 - length
# $4 - with arrow or not
#vertical_line() {
#}

clear
horizontal_line ${width_start} ${height_start} ${width} YES
echo
