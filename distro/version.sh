#!/bin/bash
# This script only display OS version, do not display other anything, because
# the git/hooks will use it.
set -e

declare __os_ver __os_ver_short

[[ ! -e /etc/os-release ]] && echo >&2 "Not found /etc/os-release" && exit 1

. /etc/os-release

__os_ver+="${NAME}"
__os_ver_short="${ID}"
if [[ ${VERSION_ID} ]]; then
	__os_ver+=" ${VERSION_ID}"
	__os_ver_short+="${VERSION_ID}"
elif [[ ${VERSION} ]]; then
	__os_ver+=" ${VERSION}"
	__os_ver_short+="$(echo ${VERSION} | grep -Eo '[0-9]+')"
fi

case $1 in
short)
	echo ${__os_ver_short}
	;;
*)
	echo ${__os_ver}
	;;
esac
