#!/bin/bash
set -e
ETHTOOL=$(which ethtool 2>/dev/null || :)

if [[ -z ${ETHTOOL} ]]; then
	echo >&2 "ERROR: not found ETHTOOL in your system"
	exit 0
fi
version=$(${ETHTOOL} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
