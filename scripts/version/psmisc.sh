#!/bin/bash
set -e
PSTREE=$(which pstree 2>/dev/null || :)
if [[ -z ${PSTREE} ]]; then
	echo >&2 "ERROR: not found PSTREE in your system"
	exit 0
fi
version=$(${PSTREE} --version 2>&1 | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
