#pragma once

extern void scx_bpf_dsq_insert(struct task_struct *p, u64 dsq_id, u64 slice,
			       u64 enq_flags) __weak __ksym;
extern s32 scx_bpf_select_cpu_dfl(struct task_struct *p, s32 prev_cpu,
				  u64 wake_flags, bool *is_idle) __weak __ksym;
