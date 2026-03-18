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
# numactl <= 2.0.14 don't has --version argument.
version=$(${NUMACTL} --version 2>/dev/null || \
	rpm -q --queryformat='%{VERSION}\n' numactl 2>/dev/null || \
	dpkg-query -W -f='${Version}\n' numactl 2>/dev/null || \
	false)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
