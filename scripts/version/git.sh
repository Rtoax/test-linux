#!/bin/bash
set -e
GIT=$(which git 2>/dev/null || :)
if [[ -z ${GIT} ]]; then
	echo >&2 "ERROR: not found GIT in your system"
	exit 0
fi
version=$(${GIT} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
