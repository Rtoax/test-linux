#!/bin/bash
set -e
NVCC=$(which nvcc 2>/dev/null || :)
[[ -z ${NVCC} ]] && [[ -e /usr/local/cuda/bin/nvcc ]] && NVCC=/usr/local/cuda/bin/nvcc

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- $(getver3 ${NVCC})
