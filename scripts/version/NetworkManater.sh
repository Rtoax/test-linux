#!/bin/bash
set -e
NMCLI=$(which nmcli 2>/dev/null || :)
if [[ -z ${NMCLI} ]]; then
	echo >&2 "ERROR: not found NMCLI in your system"
	exit 0
fi
version=$(${NMCLI} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
