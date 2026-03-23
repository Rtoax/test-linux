#!/bin/bash
set -e
NDCTL=$(which ndctl 2>/dev/null || :)
if [[ -z ${NDCTL} ]]; then
	echo >&2 "ERROR: not found NDCTL in your system"
	exit 0
fi
version=$(${NDCTL} --version | grep -Eo '[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
