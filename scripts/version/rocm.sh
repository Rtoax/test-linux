#!/bin/bash
set -e
HIPCC=$(which hipcc 2>/dev/null || :)
if [[ -z ${HIPCC} ]]; then
	echo >&2 "ERROR: not found hipcc in anywhere"
	exit 0
fi
version=$(${HIPCC} --version | grep ^HIP | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
