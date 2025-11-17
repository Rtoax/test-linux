# SPDX-License-Identifier: GPL-3.0
target-prep-y := vmlinux.h
target-bpf-y := bpf_task_from_pid.bpf.o

target-post-y := $(patsubst %.bpf.o,%.bpf.disasm,$(target-bpf-y))

include main.mk
