#!/bin/bash
# Copyright (C) 2025 Rong Tao. All rights reserved.

mylog() {
	local prio=$1 # crit, error, warning, info, debug
	shift
	logger -t "test-linux[$$]" -p ${prio} -- "$@"
}

crit() {
	mylog crit "$@"
	exit 1
}

debug() {
	mylog debug "$@"
}

error() {
	mylog error "$@"
}
