# SPDX-License-Identifier: GPL-3.0
include bpf/kfunc.mk

prep-y := vmlinux.h

kfuncs-${SUPPORT_BPF_TASK_FROM_PID} := task_from_pid
kfuncs-${SUPPORT_BPF_CGROUP_FROM_ID} += cgroup_from_id
kfuncs-${SUPPORT_BPF_CGROUP_ACQUIRE} += cgroup_acquire
kfuncs-${SUPPORT_BPF_ITER_TASK_VMA_NEW} += iter_task_vma_new

helpers-y += perf_event_output
helpers-y += strlen strnlen
helpers-y += trace_printk
helpers-${SUPPORT_BPF_STRNCMP} += strncmp
helpers-${SUPPORT_BPF_CGRP_STORAGE_GET} += cgrp_storage_get
helpers-y += get_func_ip
helpers-${SUPPORT_BPF_LOOP} += loop
helpers-y += get_current_task_btf
helpers-${SUPPORT_BPF_SEND_SIGNAL} += send_signal
helpers-${SUPPORT_BPF_SEND_SIGNAL_THREAD} += send_signal_thread

target-bpf-y := $(patsubst %,${OUTPUT}%.bpf.o,${kfuncs-y})
target-bpf-y += $(patsubst %,${OUTPUT}%.bpf.o,${helpers-y})

post-y := $(patsubst ${OUTPUT}%.bpf.o,${OUTPUT}%.bpf.disasm,$(target-bpf-y))
