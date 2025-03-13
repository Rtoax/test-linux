#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "bpf_misc.h"
#include "config-map.h"

int c = 1;
char message[12] = "Hello World";

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uint(key_size, sizeof(u32));
	__uint(value_size, sizeof(u32));
} event SEC(".maps");

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 10240);
	__type(key, u32);
	__type(value, struct msg_t);
} config_hash SEC(".maps");

#if defined(BPF_KPROBE_SYSCALL)
SEC("ksyscall/execve")
int BPF_KPROBE_SYSCALL(execve, const char *pathname)
#else
SEC("tracepoint/syscalls/sys_enter_execve")
int tracepoint__syscalls__sys_enter_execve(struct syscall_trace_enter* ctx)
#endif
{
	struct data_t data = {};
	struct msg_t *p;
	u64 uid;

	data.counter = c;
	c++;

	data.pid = bpf_get_current_pid_tgid();
	uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
	data.uid = uid;

	p = bpf_map_lookup_elem(&config_hash, &uid);

	/* Attempt to dereference a potentially null pointer */
	if (p != 0) {
		char a = p->message[0];
		bpf_printk("%d", a);
	}

	if (p != 0) {
		bpf_probe_read_kernel(&data.message, sizeof(data.message), p->message);
	} else {
		bpf_probe_read_kernel(&data.message, sizeof(data.message), message);
	}

	/**
	 * Changing this to <= means and c could have value beyond the bounds
	 * of the global message array
	 */
	if (c < sizeof(message)) {
		char a = message[c];
		bpf_printk("%c", a);
	}

	/**
	 * Changing this to <= means and c could have value beyond the bounds
	 * of the data.message array
	 */
	if (c < sizeof(data.message)) {
		char a = data.message[c];
		bpf_printk("%c", a);
	}

	bpf_get_current_comm(&data.command, sizeof(data.command));
	bpf_perf_event_output(ctx, &event, BPF_F_CURRENT_CPU,  &data, sizeof(data));

	return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
