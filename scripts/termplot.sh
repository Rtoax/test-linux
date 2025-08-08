#!/bin/bash
# Copyright (C) 2025 Rong Tao. All rights reserved.
set -e
readonly THEIGHT=$(stty size | awk '{print $1}')
readonly TWIDTH=$(stty size | awk '{print $2}')

readonly B1='┌'
readonly B2='│'
readonly B3='├'
readonly B4='└'
readonly B5='┼'
readonly B6='┤'
readonly B7='┘'
readonly B8='─'
readonly ARROW_UP='▲'
readonly ARROW_DOWN='▼'
readonly ARROW_LEFT='◀'
readonly ARROW_RIGHT='►'

readonly RED="\033[31m"
readonly GREEN="\033[32m"
readonly YELLOW="\033[33m"
readonly BLUE="\033[34m"
readonly PURPLE="\033[35m"

readonly BOLD="\033[1m"
readonly GRAY="\033[2m"
readonly ITALIC="\033[3m"
readonly UL="\033[4m" # Underline
readonly REVERSE="\033[7m"

readonly RST="\033[m"

error() {
	echo -e >&2 "${RED}ERROR: ${@}${RST}"
	exit 1
}

warning() {
	echo -e >&2 "${RED}WARNING: ${@}${RST}"
}

abs() {
	echo $(( $1 < 0 ? -$1 : $1 ));
}

gotoxy() {
	local x=$2 y=$1
	# or could use $ tput cup $y $x
	printf "\033[%d;%df" ${y} ${x}
}

pgotoxy() {
	local x=$2 y=$1
	shift 2
	printf "\033[%d;%df" ${y} ${x}
	printf "$@"
}

drawline() {
	local ix xstart xend
	local iy ystart yend
	local arrow
	local seq_args arrow_inc

	local ARGS=$(getopt --options x:X:y:Y:a \
		--long xstart: \
		--long xend: \
		--long xx: \
		--long ystart: \
		--long yend: \
		--long yy: \
		--long arrow \
		-n drawline -- "$@")

	test $? != 0 && error "$0: getopt failed"

	eval set -- "$ARGS"

	while true; do
		case $1 in
		-x | --xstart)
			shift
			xstart=$1
			shift
			;;
		-X | --xend)
			shift
			xend=$1
			shift
			;;
		--xx)
			shift
			xstart=$1
			xend=$1
			shift
			;;
		-y | --ystart)
			shift
			ystart=$1
			shift
			;;
		-Y | --yend)
			shift
			yend=$1
			shift
			;;
		--yy)
			shift
			ystart=$1
			yend=$1
			shift
			;;
		-a | --arrow)
			shift
			arrow=YES
			;;
		--)
			shift
			break
			;;
		esac
	done

	# x doesn't change, so draw a vertical line.
	if [[ ${xstart} -eq ${xend} ]]; then
		if [[ $ystart -lt $yend ]]; then
			seq_args="$ystart 1 $yend"
			arrow_inc="+ 1"
			[[ ${arrow} ]] && arrow=${ARROW_DOWN}
		else
			seq_args="$ystart -1 $yend"
			arrow_inc="- 1"
			[[ ${arrow} ]] && arrow=${ARROW_UP}
		fi

		for iy in $(seq $seq_args)
		do
			pgotoxy $iy $xstart ${B2}
		done
		pgotoxy $(($iy ${arrow_inc})) $xstart ${arrow}
	# y doesn't change, which means draw a horizontal line.
	elif [[ ${ystart} -eq ${yend} ]]; then
		if [[ $xstart -lt $xend ]]; then
			seq_args="$xstart 1 $xend"
			arrow_inc="+ 1"
			[[ ${arrow} ]] && arrow=${ARROW_RIGHT}
		else
			seq_args="$xstart -1 $xend"
			arrow_inc="- 1"
			[[ ${arrow} ]] && arrow=${ARROW_LEFT}
		fi

		for ix in $(seq $seq_args)
		do
			pgotoxy $ystart $ix ${B8}
		done
		pgotoxy $ystart $(($ix ${arrow_inc})) ${arrow}
	# Draw a diagonal line
	else
		local i dx dy abs_dx abs_dy steps
		dx=$(( xend - xstart ))
		dy=$(( yend - ystart ))

		abs_dx=$(abs $dx)
		abs_dy=$(abs $dy)

		if [ $abs_dx -ge $abs_dy ]; then
			steps=$abs_dx
		else
			steps=$abs_dy
		fi
		for (( i = 0; i <= steps; i++ )); do
			local x=$(( xstart + i * dx / steps ))
			local y=$(( ystart + i * dy / steps ))
			pgotoxy $y $x '*'
		done
	fi
}

drawcurve() {
	local X=()
	local Y=()

	local ARGS=$(getopt --options x:y: \
		-n drawcurve -- "$@")

	test $? != 0 && error "$0: getopt failed"

	eval set -- "$ARGS"

	while true; do
		case $1 in
		-x)
			shift
			X+=( $1 )
			shift
			;;
		-y)
			shift
			Y+=( $1 )
			shift
			;;
		--)
			shift
			break
			;;
		esac
	done

	[[ ${#X[@]} -ne ${#Y[@]} ]] && error "$0: Number -x != -y"

}

clear
readonly bnd=5
drawline --xstart ${bnd} --xend $((${TWIDTH} - ${bnd})) --yy $((${THEIGHT} - ${bnd})) --arrow
drawline --xx $((${TWIDTH} - ${bnd})) --ystart $((${THEIGHT} - ${bnd})) --yend ${bnd} --arrow
drawline --xstart $((${TWIDTH} - ${bnd})) --xend ${bnd} --yy ${bnd} --arrow
drawline --xx ${bnd} --ystart ${bnd} --yend $((${THEIGHT} - ${bnd})) --arrow
gotoxy ${THEIGHT} 0
echo
drawline --xstart ${bnd} --ystart ${bnd} \
	--xend $((${TWIDTH} - ${bnd})) --yend $((${THEIGHT} - ${bnd}))
drawcurve -x 1 -y 1 -x 2 -y 2
