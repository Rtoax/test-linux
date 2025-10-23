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

target-liba-y := libproc_helpers.a
target-libso-y := libproc_helpers.so

target-shell-y := mounts.sh

LDFLAGS := -Wl,-rpath,$(shell pwd)

include ../../template/main.mk

proc_examples.o: proc_helpers.h
proc_examples: ${OUTPUT}proc_examples.o libproc_helpers.so
self: ${OUTPUT}self.o libproc_helpers.so
thread-self: ${OUTPUT}thread-self.o libproc_helpers.so
auxv: ${OUTPUT}auxv.o
stat: ${OUTPUT}stat.o
uptime: ${OUTPUT}uptime.o

libproc_helpers.a: ${OUTPUT}proc_helpers.a.o
libproc_helpers.so: ${OUTPUT}proc_helpers.so.o
