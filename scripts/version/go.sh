#!/bin/bash
set -e
GO=$(which go 2>/dev/null || :)
if [[ -z ${GO} ]]; then
	echo >&2 "ERROR: not found GO in your system"
	exit 0
fi
version=$(${GO} version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
