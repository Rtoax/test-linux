#!/bin/bash
# This script only display CUDA version, do not display other anything, because
# the git/hooks will use it.
set -e
NVCC=$(which nvcc 2>/dev/null || :)
[[ -z ${NVCC} ]] && [[ -e /usr/local/cuda/bin/nvcc ]] && NVCC=/usr/local/cuda/bin/nvcc
if [[ -z ${NVCC} ]]; then
	echo >&2 "ERROR: not found nvcc in anywhere"
	exit 1
fi
version=$(${NVCC} --version | grep -Eo 'V[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version:1}
