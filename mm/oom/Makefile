sub-dir := adaptive-oom-score

targets := oom
targets += oom_minimal

VMLINUX_H := vmlinux.h
targets-prep := ${VMLINUX_H}

include ../../cgroup/libcgroup/libcgroup.mk
include ../../template/main.mk

oom_helpers.o: oom_helpers.h
proc_helpers.o: proc_helpers.h

oom: oom.o oom_helpers.o proc_helpers.o
oom_minimal: oom_minimal.o
