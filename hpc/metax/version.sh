#!/bin/bash
# This script only display HPCC version, do not display other anything, because
# the git/hooks will use it.
set -e
HPCC_PATH=$(readlink /opt/hpcc || :)
if [[ -z ${HPCC_PATH} ]]; then
	echo >&2 "ERROR: not found HPCC in your system"
	return 0
fi
echo ${HPCC_PATH} | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
