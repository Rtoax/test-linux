#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
#
# Usage: findelf.sh [DIR=<./>]
set -e

DIR=${1}
[[ -z ${DIR} ]] && DIR=./

if [[ ! -e ${DIR} ]]; then
	echo >&2 "ERROR: bad directory or file"
	exit 1
fi

while read file
do
	unset bin
	read -r -N 4 bin < $file || true
	# ELF header magic
	if [[ $bin == $'\x7f'ELF* ]]; then
		echo "$file"
	fi
done <<< $(find ${DIR} -type f)
