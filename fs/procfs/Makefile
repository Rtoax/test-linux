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

target-shell-y := mounts.sh

include ../../template/main.mk

proc_examples: ${OUTPUT}proc_examples.o ${OUTPUT}proc_helpers.o
proc_examples.o: proc_helpers.h
proc_helpers.o: proc_helpers.h
self: ${OUTPUT}self.o ${OUTPUT}proc_helpers.o
thread-self: ${OUTPUT}thread-self.o ${OUTPUT}proc_helpers.o
auxv: ${OUTPUT}auxv.o
stat: ${OUTPUT}stat.o
uptime: ${OUTPUT}uptime.o
