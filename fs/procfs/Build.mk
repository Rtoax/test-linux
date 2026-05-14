# SPDX-License-Identifier: GPL-3.0
include helpers.mk

subdir-y += process
subdir-y += procps-ng
subdir-y += kallsyms
subdir-y += modules
subdir-y += sys
subdir-y += sysrq-trigger

target-y += self thread-self
target-y += stat
target-y += uptime

target-prog-y := mounts.sh
target-prog-y += cmdline.sh
target-prog-y += diskstats.sh
target-prog-y += version.sh

self-objs := ${PROC_HELPERS}
thread-self-objs := ${PROC_HELPERS}
