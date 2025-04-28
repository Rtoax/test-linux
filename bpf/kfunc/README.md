BPF Kernel Functions (kfuncs)
=============================


- kfunc: `BPF_TRACE_FENTRY`
- kretfunc: `BPF_TRACE_FEXIT`


# Example

```c
/* Disables missing prototype warnings */
__bpf_kfunc_start_defs();

__bpf_kfunc struct task_struct *bpf_find_get_task_by_vpid(pid_t nr)
{
        return find_get_task_by_vpid(nr);
}

__bpf_kfunc_end_defs();
```


# Annotating kfunc parameters suffix

- `__sz`: `__bpf_kfunc void bpf_memzero(void *mem, int mem__sz)`
- `__k`
- `__uninit`
- `__opt`
- `__str`


# Links

- https://docs.kernel.org/bpf/kfuncs.html

