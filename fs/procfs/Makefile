# SPDX-License-Identifier: GPL-3.0
sub-dir := process
sub-dir += kallsyms

targets :=
targets += proc_examples
targets += self thread-self
targets += auxv
targets += stat
targets += statm
targets += status
targets += uptime

targets-shell := mounts.sh

include ../../template/main.mk

proc_examples: proc_examples.o proc_helpers.o
proc_examples.o: proc_helpers.h
proc_helpers.o: proc_helpers.h
self: self.o proc_helpers.o
thread-self: thread-self.o proc_helpers.o
auxv: auxv.o
stat: stat.o
statm: statm.o
status: status.o
uptime: uptime.o
