#!/bin/bash
set -e
VIM=$(which vim 2>/dev/null || :)

if [[ -z ${VIM} ]]; then
	echo >&2 "ERROR: not found VIM in your system"
	exit 0
fi
version=$(${VIM} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
