#!/bin/bash
set -e

source $(dirname $(realpath $0))/libversion.sh

LIBBPF_PATH=$(ldconfig_libver libbpf.so)

if [[ -z ${LIBBPF_PATH} ]]; then
	echo >&2 "ERROR: not found libbpf.so in anywhere"
	exit 1
fi

version=$(echo ${LIBBPF_PATH} | \
		grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

version_parser ${@} -- ${version}
