#!/bin/bash
set -e
VIRSH=$(which virsh 2>/dev/null || :)
if [[ -z ${VIRSH} ]]; then
	echo >&2 "ERROR: not found VIRSH in your system"
	exit 0
fi
version=$(${VIRSH} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
