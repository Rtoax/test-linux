#!/bin/bash
# This script only display PYTHON version, do not display other anything,
# because the git/hooks will use it.
set -e

[[ -z ${PYTHON} ]] && PYTHON=$(which python 2>/dev/null || true)
[[ -z ${PYTHON} ]] && PYTHON=$(which python3 2>/dev/null || true)

if [[ -z ${PYTHON} ]]; then
	echo >&2 "ERROR: not found python in anywhere"
	exit 1
fi

${PYTHON} --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
