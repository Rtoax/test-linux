#!/bin/bash
set -e
PS=$(which ps 2>/dev/null || :)
if [[ -z ${PS} ]]; then
	echo >&2 "ERROR: not found PS in your system"
	exit 0
fi
version=$(${PS} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
