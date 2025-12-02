BPF Scheduler Extensions sched-ext (v6.12)
===========================================

`sched_ext` is a Linux kernel feature which enables implementing kernel thread schedulers in BPF and dynamically loading them.

Register with `register_bpf_struct_ops(&bpf_sched_ext_ops, ...)`.


# Links

## Docs

- https://docs.kernel.org/scheduler/sched-ext.html
  - https://www.kernel.org/doc/html/next/scheduler/sched-ext.html
- https://docs.ebpf.io/linux/program-type/BPF_PROG_TYPE_STRUCT_OPS/sched_ext_ops/
- https://sched-ext.com/

## Code

- https://github.com/sched-ext/scx.git
- read-only: [sched-ext-release-v6.6](https://github.com/sched-ext/sched_ext/tree/sched_ext-release-v6.6)
- https://git.kernel.org/pub/scm/linux/kernel/git/tj/sched_ext.git/
