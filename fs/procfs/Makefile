# SPDX-License-Identifier: GPL-3.0
sub-dir := process

TARGETS :=
TARGETS += proc_examples
TARGETS += self thread-self
TARGETS += auxv
TARGETS += stat
TARGETS += statm
TARGETS += status
TARGETS += uptime

TARGETS_SHELL := mounts.sh

include ../../elf/pie.mk
include ../../template/main.mk

proc_examples: proc_examples.o proc_helpers.o
proc_examples.o: proc_helpers.h
proc_helpers.o: proc_helpers.h
self: self.o
thread-self: thread-self.o
auxv: auxv.o
stat: stat.o
statm: statm.o
status: status.o
uptime: uptime.o
