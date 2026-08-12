#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao
readonly LIBNBD_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
readonly KMOD_NBD_ROOT="/sys/module/nbd"

. ${LIBNBD_ROOT}/liblog.sh

__auto_modprobe_nbd() {
	if [[ ! -e ${KMOD_NBD_ROOT} ]]; then
		sudo modprobe nbd max_part=16 || error "modprobe nbd failed"
	fi
}

all_dev_ndb() {
	__auto_modprobe_nbd

	local devices=( $(ls /dev/nbd* | grep -Eo 'nbd[0-9]+') )
	echo ${devices[@]}
}

nbd_find_idle_dev() {
	local dev
	for dev in $(all_dev_ndb)
	do
		local size=$(cat /sys/block/${dev}/size)
		if [[ ${size} == 0 ]]; then
			echo ${dev}
			return 0
		fi
	done

	warning "Not found any idle nbd device"
}
