#!/bin/bash
set -e
sphinx_build=$(which sphinx-build 2>/dev/null || :)

if [[ -z ${sphinx_build} ]]; then
	echo >&2 "ERROR: not found sphinx_build in your system"
	exit 0
fi
version=$(${sphinx_build} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
