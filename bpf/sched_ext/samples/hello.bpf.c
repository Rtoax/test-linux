#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

SEC("struct_ops/select_cpu")
s32 BPF_PROG(hello_select_cpu, struct task_struct *p, s32 prev_cpu, u64 wake_flags)
{
	bool is_idle = false;
	s32 cpu;

	cpu = scx_bpf_select_cpu_dfl(p, prev_cpu, wake_flags, &is_idle);
	if (is_idle) {
		scx_bpf_dsq_insert(p, SCX_DSQ_LOCAL, SCX_SLICE_DFL, 0);
	}
	return cpu;
}

SEC("struct_ops/enqueue")
void BPF_PROG(hello_enqueue, struct task_struct *p, u64 enq_flags)
{
}

SEC("struct_ops/dispatch")
void BPF_PROG(hello_dispatch, s32 cpu, struct task_struct *prev)
{
}

SEC("struct_ops/running")
void BPF_PROG(hello_running, struct task_struct *p)
{
}

SEC("struct_ops/stopping")
void BPF_PROG(hello_stopping, struct task_struct *p, bool runnable)
{
}

SEC("struct_ops/enable")
void BPF_PROG(hello_enable, struct task_struct *p)
{
}

/* Sleelable */
SEC("struct_ops.s/init")
s32 BPF_PROG(hello_init)
{
	//return scx_bpf_create_dsq(0, -1);
	return 0;
}

SEC("struct_ops/exit")
void BPF_PROG(hello_exit, struct scx_exit_info *ei)
{
}

SEC(".struct_ops.link")
struct sched_ext_ops hello_ops = {
	.name		= "hello",
	.flags		= SCX_OPS_SWITCH_PARTIAL,
	.select_cpu	= (void *)hello_select_cpu,
	.enqueue	= (void *)hello_enqueue,
	.dispatch	= (void *)hello_dispatch,
	.running	= (void *)hello_running,
	.stopping	= (void *)hello_stopping,
	.enable		= (void *)hello_enable,
	.init		= (void *)hello_init,
	.exit		= (void *)hello_exit,
};

char __license[] SEC("license") = "GPL";
