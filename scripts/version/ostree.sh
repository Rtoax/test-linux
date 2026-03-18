#!/bin/bash
# This script only display ostree version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
OSTREE=$(which ostree 2>/dev/null || :)
if [[ -z ${OSTREE} ]]; then
	echo >&2 "ERROR: not found OSTREE in your system"
	exit 0
fi
version=$(${OSTREE} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
