#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.

readonly LIBCPU_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBCPU_ROOT}/liblog.sh

is_arch()
{
	local arches=( $@ )
	if [[ " ${arches[@]} " =~ " $(uname -m) " ]]; then
		echo YES
	fi
	return 0
}

cpu_is_hygon() {
	lscpu | grep -ow HygonGenuine
}
