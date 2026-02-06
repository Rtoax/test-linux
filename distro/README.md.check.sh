#!/bin/bash
set -e

readonly THISPATH=$(dirname $(realpath $0))

readonly kver_short=$(${THISPATH}/../scripts/kversion.sh short)
readonly os_short=$(${THISPATH}/version.sh short)

readonly README=${THISPATH}/README.md

# Show all
grep -E '^\* [0-9]+\.[0-9]+\.[0-9]+ \([^)]+\)$' ${README}

if [[ -z "$(grep -E "^\* ${kver_short} \(${os_short}\)$" ${README})" ]]; then
	echo >&2 "ERROR: Missing '* ${kver_short} (${os_short})'"
	exit 1
fi
