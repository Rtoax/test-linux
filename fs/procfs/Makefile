# SPDX-License-Identifier: GPL-3.0
OUTPUT = .output/

subdir-y := process
subdir-y += kallsyms

target-y :=
target-y += proc_examples
target-y += self thread-self
target-y += auxv
target-y += stat
target-y += uptime

libproc-helpers := libproc_helpers.so

target-liba-y := libproc_helpers.a
target-libso-y := ${libproc-helpers}

target-shell-y := mounts.sh

LDFLAGS := -Wl,-rpath,$(shell pwd)
LDFLAGS_SO_${libproc-helpers} := -Wl,--version-script=proc_helpers.map

include ../../template/main.mk

proc_examples.o: proc_helpers.h
proc_examples: ${OUTPUT}proc_examples.o ${libproc-helpers}
self: ${OUTPUT}self.o ${libproc-helpers}
thread-self: ${OUTPUT}thread-self.o ${libproc-helpers}
auxv: ${OUTPUT}auxv.o
stat: ${OUTPUT}stat.o
uptime: ${OUTPUT}uptime.o

libproc_helpers.a: ${OUTPUT}proc_helpers.a.o
${OUTPUT}proc_helpers.so.o: proc_helpers.h proc_helpers.c proc_helpers.map
${libproc-helpers}: ${OUTPUT}proc_helpers.so.o
