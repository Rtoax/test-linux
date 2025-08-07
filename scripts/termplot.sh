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
# $3 - y
# $4 - with arrow or not
horizontal_line() {
	local ix xstart xend y arrow seq_args

	xstart=$1
	xend=$2
	y=$3
	arrow=$4

	if [[ $xstart -lt $xend ]]; then
		seq_args="$xstart 1 $xend"
	else
		seq_args="$xstart -1 $xend"
	fi

	for ix in $(seq $seq_args)
	do
		gotoxy $y $ix
		printf "%s" ${B8}
	done
	[[ ${arrow} ]] && printf "%s" ${arrow}
}

# $1 - x
# $2 - y
# $3 - length
# $4 - with arrow or not
#vertical_line() {
#}

clear
horizontal_line 4 $((${TERM_WIDTH} - 0)) ${TERM_HEIGHT} ${B12}
echo
