#!/bin/bash
# This script only display numactl version, do not display other anything,
# because the git/hooks will use it.
set -e
NUMACTL=$(which numactl 2>/dev/null || :)
if [[ -z ${NUMACTL} ]]; then
	echo >&2 "ERROR: not found NUMACTL in your system"
	exit 0
fi

# only numactl v2.0.16-47-gf117290fd85c support --version argument
# https://github.com/numactl/numactl
${NUMACTL} --version 2>/dev/null || echo '< 2.0.16'
