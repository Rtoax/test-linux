#!/bin/bash
set -e
PODMAN=$(which podman 2>/dev/null || :)
if [[ -z ${PODMAN} ]]; then
	echo >&2 "ERROR: not found PODMAN in your system"
	exit 0
fi
version=$(${PODMAN} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
