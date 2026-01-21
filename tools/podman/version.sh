#!/bin/bash
# This script only display podman version, do not display other anything,
# and don't excute failed, because the git/hooks will use it.
set -e
PODMAN=$(which podman 2>/dev/null || :)
if [[ -z ${PODMAN} ]]; then
	echo >&2 "ERROR: not found PODMAN in your system"
	exit 0
fi
${PODMAN} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
