#!/bin/bash
# This script only display lingspeed gpus, do not display other anything,
# and don't excute failed, because the git/hooks will use it.
set -e

readonly NR_LINGSPEED_GPU_X710E=$(lspci -d 20e1:7101 | wc -l)
readonly NR_LINGSPEED_GPU_X710M=$(lspci -d 20e1:7103 | wc -l)
readonly NR_LINGSPEED_GPU_X710P=$(lspci -d 20e1:7104 | wc -l)

declare names

[[ ${NR_LINGSPEED_GPU_X710E} -ge 1 ]] && names+=" X710Ex${NR_LINGSPEED_GPU_X710E}"
[[ ${NR_LINGSPEED_GPU_X710M} -ge 1 ]] && names+=" X710Mx${NR_LINGSPEED_GPU_X710M}"
[[ ${NR_LINGSPEED_GPU_X710P} -ge 1 ]] && names+=" X710Px${NR_LINGSPEED_GPU_X710P}"

if [[ "${names}" ]]; then
	echo "Lingspeed${names}"
fi
