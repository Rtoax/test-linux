#!/bin/bash
# Usage: [FLR/FORCE=1] [VLR=1|VERBOSE=1] ./linux-reference.sh
set -e

[[ -z ${FLR} ]] && FLR=${FORCE}

readonly THISPATH=$(dirname $(realpath $0))

readonly kver_short=$(${THISPATH}/../version/kversion.sh short)
readonly os_short=$(${THISPATH}/../version/distro.sh short)
readonly os_short_name=$(${THISPATH}/../version/distro.sh short-name)

readonly README_DOC=$(realpath ${THISPATH}/../../Documentation/distro/linux-reference.rst)
readonly DISTRO_DOC=$(realpath ${THISPATH}/../../Documentation/distro/${os_short_name}.rst)

if [[ -f ${THISPATH}/../../.gitconfig.sh ]]; then
	. ${THISPATH}/../../.gitconfig.sh
fi

force_exit() {
	if [[ -z ${FLR} ]]; then
		echo >&2 "ERROR: set FLR=1/FORCE=1 to skip"
		exit 1
	fi
}

if [[ ! -f ${DISTRO_DOC} ]]; then
	echo >&2 "ERROR: ${DISTRO_DOC} is not exist, please create it"
	force_exit
fi

if ! grep --quiet "^- $(uname -r)$" ${DISTRO_DOC}; then
	echo >&2 "ERROR: ${DISTRO_DOC} is not contains '$(uname -r)', please add it"
	force_exit
fi

# Show all
[[ ${VLR}${VERBOSE} ]] && grep -E '^\* [0-9]+\.[0-9]+\.[0-9]+ \([^)]+\)$' ${README_DOC}

if [[ -z "$(grep -E "^\* ${kver_short} \(.*${os_short}.*\)$" ${README_DOC})" ]]; then
	oldline=$(grep -E "^\* ${kver_short} \([^)]+\)$" ${README_DOC} || :)
	if [[ ! -z ${oldline} ]]; then
		echo >&2 "ERROR: Missing '${os_short}' in '${oldline}' in ${README_DOC}"
	else
		echo >&2 "ERROR: Missing '* ${kver_short} (${os_short})' in ${README_DOC}"
	fi
	force_exit
fi
