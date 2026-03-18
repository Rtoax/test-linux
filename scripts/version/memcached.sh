#!/bin/bash
set -e
MEMCACHED=$(which memcached 2>/dev/null || :)
if [[ -z ${MEMCACHED} ]]; then
	echo >&2 "ERROR: not found MEMCACHED in your system"
	exit 0
fi

version=$(${MEMCACHED} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
