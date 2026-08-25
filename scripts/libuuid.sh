#!/bin/bash
# SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
# Copyright (C) 2026 Rong Tao. All rights reserved.

__gen_uuid_od() {
	rand_xxxx() {
		od -An -N2 -t x2 /dev/random | awk '{print $1}'
	}
	rand_xxxxxxxx() {
		od -An -N4 -t x4 /dev/random | awk '{print $1}'
	}
	local v1=$(rand_xxxxxxxx)
	local v2=$(rand_xxxx)
	local v3=$(rand_xxxx)
	local v4=$(rand_xxxx)
	local v51=$(rand_xxxxxxxx)
	local v52=$(rand_xxxx)
	echo ${v1}-${v2}-${v3}-${v4}-${v51}${v52}
}

gen_uuid() {
	if [[ -e /proc/sys/kernel/random/uuid ]]; then
		cat /proc/sys/kernel/random/uuid
	elif which od 2>/dev/null; then
		__gen_uuid_od
	elif which uuid 2>/dev/null; then
		uuid -m
	else
		echo eacb9c42-9690-11f1-98af-f02f74946cb8
	fi
}
