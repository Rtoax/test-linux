#!/bin/bash
set -e

source $(dirname $(realpath $0))/libversion.sh

LIBXDP_PATH=$(ldconfig_libver libxdp.so)

if [[ -z ${LIBXDP_PATH} ]]; then
	echo >&2 "ERROR: not found libxdp.so in anywhere"
	exit 0
fi

version=$(echo ${LIBXDP_PATH} | \
		grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

version_parser ${@} -- ${version}
