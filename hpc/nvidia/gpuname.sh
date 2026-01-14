#!/bin/bash
# This script only display nvidia gpus, do not display other anything,
# and don't excute failed, because the git/hooks will use it.
#
set -e

NVSMI=$(which nvidia-smi 2>/dev/null || true)

if [[ -z ${NVSMI} ]]; then
	echo >&2 "ERROR: Not found nvidia-smi in any where, do you install cuda toolkit??"
	exit 0
fi

${NVSMI} --query-gpu=name | grep -v ^name
