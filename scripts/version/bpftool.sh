#!/bin/bash
set -e
BPFTOOL=$(which bpftool 2>/dev/null || :)
if [[ -z ${BPFTOOL} ]]; then
	echo >&2 "ERROR: not found BPFTOOL in your system"
	exit 0
fi
version=$(${BPFTOOL} --version | grep ^bpftool | \
		grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
