#!/bin/bash
set -e
BPFTRACE=$(which bpftrace 2>/dev/null || :)
if [[ -z ${BPFTRACE} ]]; then
	echo >&2 "ERROR: not found BPFTRACE in your system"
	exit 0
fi
version=$(${BPFTRACE} --version | grep -Eo 'v[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version:1}
