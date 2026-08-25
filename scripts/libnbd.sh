#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.
readonly LIBNBD_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
readonly KMOD_NBD_ROOT="/sys/module/nbd"

. ${LIBNBD_ROOT}/liblog.sh

# VALID_NBD_DEV: no one use this nbd device
# BUSY_NBD_DEV: nbd device already used
declare -a ALL_NBD_DEV VALID_NBD_DEV BUSY_NBD_DEV

__auto_modprobe_nbd() {
	if [[ ! -e ${KMOD_NBD_ROOT} ]]; then
		sudo modprobe nbd max_part=16 || error "modprobe nbd failed"
	fi
}

# Auto probe nbd driver and statistic
__auto_update_nbd_devices() {
	local nbd

	__auto_modprobe_nbd

	# Partitions not appear in /sys/block/
	ALL_NBD_DEV=( $(ls /dev/nbd* | grep -Eo 'nbd[0-9]+') )

	# Reset valid NBD
	unset VALID_NBD_DEV
	unset BUSY_NBD_DEV
	for nbd in ${ALL_NBD_DEV[@]}
	do
		if [[ -e /sys/block/${nbd}/pid ]]; then
			BUSY_NBD_DEV+=( ${nbd} )
		else
			VALID_NBD_DEV+=( ${nbd} )
		fi
	done
}

all_dev_ndb() {
	__auto_modprobe_nbd
	__auto_update_nbd_devices

	echo ${ALL_NBD_DEV[@]}
}

# echo device with '/dev/' prefix
nbd_find_idle_dev() {
	__auto_update_nbd_devices

	local dev
	for dev in $(all_dev_ndb)
	do
		local size=$(cat /sys/block/${dev}/size)
		if [[ ${size} == 0 ]]; then
			echo "/dev/${dev}"
			return 0
		fi
	done

	warning "Not found any idle nbd device"
}
