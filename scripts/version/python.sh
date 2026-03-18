#!/bin/bash
set -e

[[ -z ${PYTHON} ]] && PYTHON=$(which python 2>/dev/null || true)
[[ -z ${PYTHON} ]] && PYTHON=$(which python3 2>/dev/null || true)

if [[ -z ${PYTHON} ]]; then
	echo >&2 "ERROR: not found python in anywhere"
	exit 1
fi

version=$(${PYTHON} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
