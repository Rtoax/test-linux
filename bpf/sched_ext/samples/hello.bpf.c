#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

SEC("struct_ops/select_cpu")
s32 hello_select_cpu(struct task_struct *p, s32 prev_cpu, u64 wake_flags)
{
	return 2;
}

SEC("struct_ops/enqueue")
void hello_enqueue(struct task_struct *p, u64 enq_flags)
{
}

SEC("struct_ops/dispatch")
void hello_dispatch(s32 cpu, struct task_struct *prev)
{
}

SEC("struct_ops/running")
void hello_running(struct task_struct *p)
{
}

SEC("struct_ops/stopping")
void hello_stopping(struct task_struct *p, bool runnable)
{
}

SEC("struct_ops/enable")
void hello_enable(struct task_struct *p)
{
}

SEC("struct_ops.s/init")
s32 hello_init(void)
{
	return 0;
}

SEC("struct_ops/exit")
void hello_exit(struct scx_exit_info *ei)
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
