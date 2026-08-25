#!/bin/bash
set -e

# linux::kernel/printk/printk.c
#define LOG_LEVEL(v)		((v) & 0x07)
#define LOG_FACILITY(v)		((v) >> 3 & 0xff)

__kmsg_log() {
	local lvl=$1
	shift
	echo "<${lvl}>test-linux[$$] ${@}" | sudo tee /dev/kmsg
}

kmsg_fatal() {
	__kmsg_log 2 ${@}
}

kmsg_error() {
	__kmsg_log 3 ${@}
}

kmsg_warn() {
	__kmsg_log 4 ${@}
}

kmsg_info() {
	__kmsg_log 6 ${@}
}

kmsg_debug() {
	__kmsg_log 7 ${@}
}

kmsg_fatal `date`
kmsg_error `date`
kmsg_warn `date`
kmsg_info `date`
kmsg_debug `date`
