#!/bin/bash
# This script only display systemd version, do not display other anything,
# and don't excute failed, because the git/hooks will use it.
set -e
SYSTEMCTL=$(which systemctl 2>/dev/null || :)
if [[ -z ${SYSTEMCTL} ]]; then
	echo >&2 "ERROR: not found SYSTEMD in your system"
	exit 0
fi
${SYSTEMCTL} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true
