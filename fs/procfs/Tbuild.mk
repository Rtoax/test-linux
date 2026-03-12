# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

subdir-y := process
subdir-y += procps-ng
subdir-y += kallsyms
subdir-y += sys
subdir-y += sysrq-trigger

target-y += proc_examples
target-y += self thread-self
target-y += stat
target-y += uptime

libproc-helpers := libproc_helpers.so.0.1.0

target-liba-y := libproc_helpers.a
target-libso-y := ${libproc-helpers}

target-shell-y := mounts.sh
target-shell-y += cmdline.sh
target-shell-y += diskstats.sh
target-shell-y += version.sh

libproc_helpers.a-objs := ${OUTPUT}proc_helpers.a.o
${libproc-helpers}-objs := ${OUTPUT}proc_helpers.so.o

proc_examples-objs := ${libproc-helpers}
self-objs := ${libproc-helpers}
thread-self-objs := ${libproc-helpers}

LDFLAGS := -Wl,-rpath,$(shell pwd)
LDFLAGS_SO_${libproc-helpers} := -Wl,--version-script=proc_helpers.map
