#!/bin/bash
# Copyright (C) 2025 Rong Tao. All rights reserved.
set -e

readonly kconfig=/boot/config-$(uname -r)

declare -a configs

[[ -f ${kconfig} ]] && source ${kconfig}

if [[ ${CONFIG_DEBUG_INFO_BTF} ]]; then
	configs+=( HAVE_BTF=y )
fi

if [[ -e /usr/include/bpf/libbpf.h ]]; then
	configs+=( HAVE_LIBBPF=y )
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
		echo "$config" >> $file
	done
}
