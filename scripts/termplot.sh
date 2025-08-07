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
	local seq_args arrow_inc

	xstart=$1
	xend=$2
	ystart=$3
	yend=$4
	arrow=$5

	if [[ ${xstart} -eq ${xend} ]]; then
		if [[ $ystart -lt $yend ]]; then
			seq_args="$ystart 1 $yend"
			arrow_inc="+ 1"
			[[ ${arrow} ]] && arrow=${B10}
		else
			seq_args="$ystart -1 $yend"
			arrow_inc="- 1"
			[[ ${arrow} ]] && arrow=${B9}
		fi

		for iy in $(seq $seq_args)
		do
			gotoxy $iy $xstart
			printf "%s" ${B2}
		done
		gotoxy $(($iy ${arrow_inc})) $xstart
		printf "%s" ${arrow}
	elif [[ ${ystart} -eq ${yend} ]]; then
		if [[ $xstart -lt $xend ]]; then
			seq_args="$xstart 1 $xend"
			arrow_inc="+ 1"
			[[ ${arrow} ]] && arrow=${B12}
		else
			seq_args="$xstart -1 $xend"
			arrow_inc="- 1"
			[[ ${arrow} ]] && arrow=${B11}
		fi

		for ix in $(seq $seq_args)
		do
			gotoxy $ystart $ix
			printf "%s" ${B8}
		done
		gotoxy $ystart $(($ix ${arrow_inc}))
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

# $1 - y start
# $2 - y end
# $3 - x
# $4 - with arrow or not
vertical_line() {
	drawline $3 $3 $1 $2 $4
}

clear
horizontal_line 4 $((${TERM_WIDTH} - 4)) ${TERM_HEIGHT} YES
horizontal_line $((${TERM_WIDTH} - 4)) 4 $((${TERM_HEIGHT} - 2)) YES
vertical_line 4 $((${TERM_HEIGHT} - 4)) ${TERM_WIDTH} YES
vertical_line $((${TERM_HEIGHT} - 4)) 4 $((${TERM_WIDTH} - 2 )) YES
gotoxy ${TERM_HEIGHT} 0
echo
