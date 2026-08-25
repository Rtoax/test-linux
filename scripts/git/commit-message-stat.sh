#!/bin/bash
# Copyright (C) 2026 Rong Tao. All rights reserved.
#
# Usage: commit-message-stat.sh [downer-commit] [upper-commit]
set -e

from_commit=$1
to_commit=$2
COMMITS_ARG=

if [[ ${from_commit} ]] && [[ ${to_commit} ]]; then
	COMMITS_ARG=${from_commit}..${to_commit}
elif [[ ${from_commit} ]]; then
	echo >&2 "ERROR: need two commits at least"
	exit 1
fi

# Statistic os
stat_os_sed() {
	git log ${COMMITS_ARG} --format=%B | \
		grep -E "Vers(ions)?:" | \
		sed -E 's/.*Vers(ions)?: ([^,]*),.*/\2/' | \
		grep -vE "Vers(ions)?:" | sort | uniq -c
}
stat_os_awk() {
	git log ${COMMITS_ARG} --format=%B | \
		awk '/Vers(ions)?:/ {split($0, a, ","); sub(/.*Vers(ions)?: /, "", a[1]); print a[1]}' | \
		grep -vE "Vers(ions)?:" | sort | uniq -c
}

stat_linux() {
	git log ${COMMITS_ARG} --format=%B | \
		awk -F', ' '/Vers:/ {print $2}' | sort | uniq -c
}

stat_arch() {
	git log ${COMMITS_ARG} --format=%B | \
		grep "Envs:" | grep -oP 'Arch \K\S+' | sed 's/,$//' | sort | uniq -c
}

echo "------------- linux ---------------"
stat_linux
echo "------------- os ---------------"
os_sed="$(stat_os_sed)"
os_awk="$(stat_os_awk)"
if [[ "${os_sed}" != "${os_awk}" ]]; then
	echo >&2 "ERROR: stat os sed != awk"
	exit 1
fi
echo "${os_sed}"
echo "------------- arch ---------------"
stat_arch
