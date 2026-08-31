#!/bin/bash

PLOTCAKE=$(which plotcake 2>/dev/null || true)
if [[ -z ${PLOTCAKE} ]]; then
	PLOTCAKE=../plotcake
fi
if [[ ! -e ${PLOTCAKE} ]]; then
	echo >&2 "ERROR: Not found plotcake, please compile and install it"
	exit 1
fi
