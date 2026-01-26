#!/bin/bash
# This script only display OS version, do not display other anything, because
# the git/hooks will use it.
set -e

declare __os_ver
[[ ! -e /etc/os-release ]] && echo >&2 "Not found /etc/os-release" && exit 1

. /etc/os-release
__os_ver+="${NAME}"
if [[ ${VERSION_ID} ]]; then
	__os_ver+=" ${VERSION_ID}"
elif [[ ${VERSION} ]]; then
	__os_ver+=" ${VERSION}"
fi

echo ${__os_ver}
