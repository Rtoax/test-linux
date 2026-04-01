#!/bin/bash
set -e
DRACUT=$(which dracut 2>/dev/null || :)

if [[ -z ${DRACUT} ]]; then
	echo >&2 "ERROR: not found DRACUT in your system"
	exit 0
fi
version=$(${DRACUT} --version | grep -Eo '[0-9]+\-[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} --seperator '-' -- ${version}
