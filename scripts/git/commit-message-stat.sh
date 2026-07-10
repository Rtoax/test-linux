#!/bin/bash
# Copyright (C) 2026 Rong Tao
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
stat_os() {
	git log ${COMMITS_ARG} --format=%B | \
		grep "Vers:" | sed -E 's/.*Vers: ([^,]*),.*/\1/' | sort | uniq -c
}
stat_os_awk() {
	git log ${COMMITS_ARG} --format=%B | \
		awk '/Vers:/ {split($0, a, ","); sub(/.*Vers: /, "", a[1]); print a[1]}' | sort | uniq -c
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
stat_os
echo "------------- arch ---------------"
stat_arch
