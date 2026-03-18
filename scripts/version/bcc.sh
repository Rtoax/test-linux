#!/bin/bash
set -e

LIBBCC_PATH=$(realpath $(ldconfig -p | grep libbcc.so 2>/dev/null | awk '{print $NF}' | head -1) 2>/dev/null || :)

if [[ -z ${LIBBCC_PATH} ]]; then
	echo >&2 "ERROR: not found libbcc.so in anywhere"
	exit 1
fi

version=$(echo ${LIBBCC_PATH} | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
