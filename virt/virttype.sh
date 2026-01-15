#!/bin/bash
# WARNING: This script be called in git/hooks/prepare-commit-msg
#
# Display virtual type in stdin, 'none' if running on physical machine.
set -e

virttype=

SYSTEMD_DETECT_VIRT=$(which systemd-detect-virt 2>/dev/null || :)
if [[ ${SYSTEMD_DETECT_VIRT} ]]; then
	virt=$( ${SYSTEMD_DETECT_VIRT} || : )
	if [[ ${virt} != none ]]; then
		virttype=${virt}
	fi
fi

if [[ ${virttype} ]]; then
	echo ${virttype}
else
	echo Physical Machine
fi
