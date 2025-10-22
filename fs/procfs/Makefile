# SPDX-License-Identifier: GPL-3.0
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

proc_examples: proc_examples.o proc_helpers.o
proc_examples.o: proc_helpers.h
proc_helpers.o: proc_helpers.h
self: self.o proc_helpers.o
thread-self: thread-self.o proc_helpers.o
auxv: auxv.o
stat: stat.o
uptime: uptime.o
