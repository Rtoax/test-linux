#!/bin/bash
#
# Export definitions:
# - LSSMI=/usr/bin/ls-smi
# - LINGSPEED_GPUS=[...]
# - GPU_NAME=X710-E:2
#

LSSMI=$(which ls-smi 2>/dev/null || true)

if [[ -z ${LSSMI} ]]; then
	echo >&2 "ERROR: Not found ls-smi in any where, do you install lingspeed-driver??"
	exit 1
fi

LINGSPEED_GPUS=( $(${LSSMI} | grep -oe "X710-[E|M|P]") )
if [[ ${#LINGSPEED_GPUS[@]} -eq 0 ]]; then
	echo >&2 "ERROR: Not found any lingspeed GPUs in your system"
	exit 1
fi

get_lingspeed_gpu_name() {
	local name
	local -A type_count
	for name in ${LINGSPEED_GPUS[@]}
	do
		if [[ -n ${type_count[$name]} ]]; then
			type_count[$name]=$(( ${type_count[$name]} + 1 ))
		else
			type_count[$name]=1
		fi
	done

	for name in "${!type_count[@]}"
	do
		printf "${name}:${type_count[$name]}"
	done
}

GPU_NAME=$(get_lingspeed_gpu_name)
echo ${GPU_NAME}
