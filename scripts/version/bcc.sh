#!/bin/bash
set -e

source $(dirname $(realpath $0))/libversion.sh

LIBBCC_PATH=$(ldconfig_libver libbcc.so)

if [[ -z ${LIBBCC_PATH} ]]; then
	echo >&2 "ERROR: not found libbcc.so in anywhere"
	exit 1
fi

version=$(echo ${LIBBCC_PATH} | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

version_parser ${@} -- ${version}
