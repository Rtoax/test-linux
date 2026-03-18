#!/bin/bash
# This script only display pahole version, do not display other anything,
# because the git/hooks will use it.
#
# Usage: pahole.sh [--major|--minor]
#
set -e
PAHOLE=$(which pahole 2>/dev/null || :)
if [[ -z ${PAHOLE} ]]; then
	echo >&2 "ERROR: not found PAHOLE in your system"
	exit 0
fi
version=$( ${PAHOLE} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true )

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
