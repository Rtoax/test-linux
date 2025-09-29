#!/bin/bash
# Copyright (C) 2025 Rong Tao. All rights reserved.
set -e

readonly kconfig=/boot/config-$(uname -r)

declare -a configs

[[ -f ${kconfig} ]] && source ${kconfig}

[[ ${CONFIG_DEBUG_INFO_BTF} ]] && configs+=( HAVE_BTF=y )
[[ -e /usr/include/bpf/libbpf.h ]] && configs+=( HAVE_LIBBPF=y )
[[ -e /opt/hpcc/ ]] && configs+=( HAVE_HPCC=y )
[[ -e /usr/include/hip/ ]] && configs+=( HAVE_HIP=y )
[[ -e /usr/include/hipblas/ ]] && configs+=( HAVE_HIP_BLAS=y )

if [[ -e /usr/local/cuda/include/cuda.h ]] || [[ -e /usr/include/cuda.h ]]; then
	configs+=( HAVE_CUDA=y )
fi

# $1 - filename
write_configs_to_file() {
	local i
	local file=$1

	if [[ -f $file ]]; then
		mv $file $file.old
	fi

	for config in "${configs[@]}"
	do
		echo "$config"
	done >> $file
}
