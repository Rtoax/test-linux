#!/bin/bash
# This script only display CUDA version, do not display other anything, because
# the git/hooks will use it.
set -e
NVCC=$(which nvcc 2>/dev/null || :)
if [[ -z ${NVCC} ]]; then
	echo >&2 "ERROR: not found nvcc in anywhere"
	exit 1
fi
${NVCC} --version | grep -Eo 'V[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true
