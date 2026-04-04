#!/bin/bash
# Usage: [FLR/FORCE=1] [V=1|VERBOSE=1] ./linux-reference.sh
set -e

FLR=${FORCE}

readonly THISPATH=$(dirname $(realpath $0))

readonly kver_short=$(${THISPATH}/../kversion.sh short)
readonly os_short=$(${THISPATH}/../version/distro.sh short)

readonly README=$(realpath ${THISPATH}/../../Documentation/distro/linux-reference.rst)

# Show all
[[ ${V}${VERBOSE} ]] && grep -E '^\* [0-9]+\.[0-9]+\.[0-9]+ \([^)]+\)$' ${README}

if [[ -z "$(grep -E "^\* ${kver_short} \(.*${os_short}.*\)$" ${README})" ]]; then
	oldline=$(grep -E "^\* ${kver_short} \([^)]+\)$" ${README} || :)
	if [[ ! -z ${oldline} ]]; then
		echo >&2 "ERROR: Missing '${os_short}' in '${oldline}' in ${README}"
	else
		echo >&2 "ERROR: Missing '* ${kver_short} (${os_short})' in ${README}"
	fi
	[[ -z ${FLR} ]] && exit 1
fi
