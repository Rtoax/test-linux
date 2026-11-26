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

readonly LINE_TYPES=( $(${PLOTCAKE} --draws 2>/dev/null || true) )
readonly LINE_TYPES_ARGS=( $(for t in ${LINE_TYPES[@]}; do echo "-D ${t}"; done) )
readonly LINE_TYPES_CONST=( unicode-bold unicode-bold-dashed unicode-boldbold
			    unicode unicode-dashed unicode-area-chart utf8
			    unicode-heart )

readonly LINE_COLORS=( $(${PLOTCAKE} --colors 2>/dev/null || true) )
readonly LINE_COLORS_ARGS=( $(for t in ${LINE_COLORS[@]}; do echo "-C ${t}"; done) )
readonly LINE_COLORS_CONST=( green red cyan white magenta blue yellow )
readonly SUPPORT_JSON="$(${PLOTCAKE} --help | grep -wo json)"

plotcake_reset()
{
	#if which reset 2>&1 >/dev/null; then
	#	reset || :
	#fi
	if which resize 2>&1 >/dev/null; then
		resize 2>&1 >/dev/null || :
	fi
}

__plotcake_reset()
{
	local err=$?
	plotcake_reset
	exit ${err}
}
trap __plotcake_reset EXIT
