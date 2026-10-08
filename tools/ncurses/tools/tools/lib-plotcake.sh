#!/bin/bash

readonly PLOTCAKE_ROOT=$(realpath $(dirname $(readlink -f ${BASH_SOURCE[0]}))/..)

if [[ -z ${PLOTCAKE} ]] && [[ -f ${PLOTCAKE_ROOT}/plotcake ]]; then
	PLOTCAKE=${PLOTCAKE_ROOT}/plotcake
fi

[[ -z ${PLOTCAKE} ]] && PLOTCAKE=$(which plotcake 2>/dev/null || true)

if [[ ! -e ${PLOTCAKE} ]]; then
	echo >&2 "ERROR: Not found plotcake, please compile and install it"
	exit 1
fi

readonly LINE_TYPES=( $(${PLOTCAKE} --ltypes 2>/dev/null || true) )
readonly LINE_TYPES_ARGS=( $(for t in ${LINE_TYPES[@]}; do echo "-L ${t}"; done) )
readonly LINE_TYPES_CONST=( unicode-bold unicode-bold-dashed unicode-boldbold
			    unicode unicode-dashed unicode-area-chart utf8
			    unicode-heart )

readonly LINE_COLORS=( $(${PLOTCAKE} --lcolors 2>/dev/null || true) )
readonly LINE_COLORS_ARGS=( $(for t in ${LINE_COLORS[@]}; do echo "-C ${t}"; done) )
readonly LINE_COLORS_CONST=( green red cyan white magenta blue yellow )
readonly SUPPORT_JSON="$(${PLOTCAKE} --help | grep -wo json)"

plotcake_reset()
{
	local err=$?
	resize 2>&1 >/dev/null || true
	# reset 2>&1 >/dev/null || true
	echo >&2 "Bye!"
	exit ${err}
}
trap plotcake_reset EXIT
