#!/bin/bash

if [[ -z ${PLOTCAKE} ]] && [[ -f ../plotcake ]]; then
	PLOTCAKE=../plotcake
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
