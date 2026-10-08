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

plotcake_reset()
{
	local err=$?
	resize 2>&1 >/dev/null || true
	# reset 2>&1 >/dev/null || true
	echo >&2 "Bye!"
	exit ${err}
}
trap plotcake_reset EXIT
