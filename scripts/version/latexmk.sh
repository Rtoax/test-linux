#!/bin/bash
set -e
latexmk=$(which latexmk 2>/dev/null || :)

if [[ -z ${latexmk} ]]; then
	echo >&2 "ERROR: not found latexmk in your system"
	exit 0
fi
version=$(${latexmk} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
