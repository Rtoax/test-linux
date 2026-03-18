#!/bin/bash
# This script only display libvirt version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: libvirt.sh [--major|--minor|--patchlevel]
#
set -e
VIRSH=$(which virsh 2>/dev/null || :)
if [[ -z ${VIRSH} ]]; then
	echo >&2 "ERROR: not found VIRSH in your system"
	exit 0
fi
version=$(${VIRSH} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
