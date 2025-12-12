# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

subdir-y := process
subdir-y += kallsyms
subdir-y += sys
subdir-y += sysrq-trigger

target-y :=
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

LDFLAGS := -Wl,-rpath,$(shell pwd)
LDFLAGS_SO_${libproc-helpers} := -Wl,--version-script=proc_helpers.map

include main.mk

proc_examples.o: proc_helpers.h
proc_examples: ${OUTPUT}proc_examples.o ${libproc-helpers}
self: ${OUTPUT}self.o ${libproc-helpers}
thread-self: ${OUTPUT}thread-self.o ${libproc-helpers}
stat: ${OUTPUT}stat.o
uptime: ${OUTPUT}uptime.o

libproc_helpers.a: ${OUTPUT}proc_helpers.a.o
${OUTPUT}proc_helpers.so.o: proc_helpers.h proc_helpers.c proc_helpers.map
${libproc-helpers}: ${OUTPUT}proc_helpers.so.o
