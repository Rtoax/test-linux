#!/bin/bash
# Usage: I=<0.1> TMOUT=<1s> ./examples.sh

# -m: (set -o monitor) monitor mode
set -em
readonly LOG=${0}.log
readonly PLOTCAKE=./plotcake

readonly LINE_TYPES=( $(${PLOTCAKE} --ltypes 2>/dev/null || true) )
readonly LINE_TYPES_ARGS=( $(for t in ${LINE_TYPES[@]}; do echo "-L ${t}"; done) )

readonly LINE_COLORS=( $(${PLOTCAKE} --lcolors 2>/dev/null || true) )
readonly LINE_COLORS_ARGS=( $(for t in ${LINE_COLORS[@]}; do echo "-C ${t}"; done) )

[[ -z ${I} ]] && I=0.001
[[ -z ${TMOUT} ]] && TMOUT=200ms

Interval=${I}

args=( -t ${TMOUT} --tmout ${TMOUT} )
args+=( -v --verbose )
args+=( ${@} )

# plotcake will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed, just for test in Build.mk's
# `prog-y`.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

_eval() {
	eval "${@}"
	echo "${@}" | tee --append ${LOG}
}

# $1: type: none
#     none: 1 2 3 4 ...
# $2: num
_seq() {
	local TYPE=$1
	shift
	local NUM=$1
	shift
	case $TYPE in
	none | *)
		seq --separator=' ' 1 1 ${NUM}
		;;
	esac
}

run() {
	_eval ${PLOTCAKE} ${args[@]} -I 10ms --interval=10ms "${@}"
}

# $1: line number
__stdin() {
	local NUM=$1
	shift
	while _seq none ${NUM}; do
		sleep ${Interval}
	done | _eval ${PLOTCAKE} ${args[@]} "${@}"
}
stdin() {
	__stdin ${#LINE_TYPES[@]} "${@}"
	__stdin ${#LINE_COLORS[@]} "${@}"
}

# __main__
rm -f ${LOG}

if [[ " ${LINE_TYPES[@]} " != " unicode-bold unicode-bold-dashed unicode-boldbold unicode unicode-dashed unicode-area-chart utf8 unicode-heart " ]]; then
	echo >&2 "ERROR: line types not match!"
	exit 1
fi

if [[ " ${LINE_COLORS[@]} " != " green red cyan white magenta blue yellow " ]]; then
	echo >&2 "ERROR: line color not match!"
	exit 1
fi

run -? --help
run --usage
run --lcolors
run --ltypes
run -V --version
run -M --ram
stdin --title 'test title' --xlabel XLABEL --ylabel YLABEL -C red -C red
run ${LINE_TYPES_ARGS[@]} ${LINE_COLORS_ARGS[@]}
run -o data
run -f data.txt
run --logarithmic
run --logarithmic10
run --exponential

stdin -V --version
stdin --usage
stdin -? --help
stdin --title 'test title' --xlabel XLABEL --ylabel YLABEL -C red -C red
stdin ${LINE_TYPES_ARGS[@]} ${LINE_COLORS_ARGS[@]}
stdin --logarithmic
stdin --logarithmic10
stdin --exponential

while true; do
	for i in 2 4 1 4 6 1 9 1 2 3 4 5; do
		seq --separator=' ' 1 1 $i
		sleep ${Interval}
	done
done | ${PLOTCAKE} ${args[@]}

echo "Byebye"
