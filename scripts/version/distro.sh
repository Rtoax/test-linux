#!/bin/bash
# Usage: distro.sh [short]
set -e

declare name_full name_short pretty_name ver_num

[[ ! -e /etc/os-release ]] && echo >&2 "Not found /etc/os-release" && exit 1

. /etc/os-release

name_full="${NAME}"
name_short="${ID}"
pretty_name="${PRETTY_NAME}"

if [[ ${DEBIAN_VERSION_FULL} ]]; then
	ver_num=${DEBIAN_VERSION_FULL}
else
	if [[ ${VERSION_ID} ]]; then
		ver_num=${VERSION_ID}
	elif [[ ${VERSION} ]]; then
		ver_num="$(echo ${VERSION} | grep -Eo -e '[0-9]+\.[0-9]+' -e '[0-9]+')"
	fi
fi

case $1 in
short)
	echo "${name_short}${ver_num}"
	;;
*)
	if [[ -z ${pretty_name} ]]; then
		echo "${name_full} ${ver_num}"
	else
		echo "${pretty_name}"
	fi
	;;
esac
