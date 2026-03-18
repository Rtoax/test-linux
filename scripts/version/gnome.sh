#!/bin/bash
# This script only display gnome-shell version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
set -e
GNOME=$(which gnome-shell 2>/dev/null || :)
if [[ -z ${GNOME} ]]; then
	echo >&2 "ERROR: not found GNOME in your system"
	exit 0
fi
version=$(${GNOME} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
