#!/bin/bash
# This script only display cmake version, do not display other anything,
# because the git/hooks will use it.
set -e
cmake=$(which cmake 2>/dev/null || :)
if [[ -z ${cmake} ]]; then
	echo >&2 "ERROR: not found cmake in your system"
	exit 0
fi

version=$( ${cmake} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true )
echo ${version}
