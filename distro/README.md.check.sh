#!/bin/bash
# Usage: [V=1|VERBOSE=1] ./README.md.check.sh
set -e

readonly THISPATH=$(dirname $(realpath $0))

readonly kver_short=$(${THISPATH}/../scripts/kversion.sh short)
readonly os_short=$(${THISPATH}/../scripts/version/distro.sh short)

readonly README=${THISPATH}/README.md

# Show all
[[ ${V}${VERBOSE} ]] && grep -E '^\* [0-9]+\.[0-9]+\.[0-9]+ \([^)]+\)$' ${README}

if [[ -z "$(grep -E "^\* ${kver_short} \(.*${os_short}.*\)$" ${README})" ]]; then
	oldline=$(grep -E "^\* ${kver_short} \([^)]+\)$" ${README} || :)
	if [[ ! -z ${oldline} ]]; then
		echo >&2 "ERROR: Missing '${os_short}' in '${oldline}' in ${README}"
	else
		echo >&2 "ERROR: Missing '* ${kver_short} (${os_short})' in ${README}"
	fi
	exit 1
fi
