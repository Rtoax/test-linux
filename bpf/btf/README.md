BTF (BPF Type Format)
=====================

# BTF Types

- `BTF_KIND_DECL_TAG`: Declaration Tag


# /sys/kernel/btf/

* `/sys/kernel/btf/vmlinux`
	* `btf_vmlinux_init()`
	* `btf_vmlinux_read()`
* `/sys/kernel/btf/kvm`


# pahole

Shows, manipulates data structure layout and pretty prints raw data.

* [pahole.git](https://git.kernel.org/pub/scm/devel/pahole/pahole.git/)

The `pahole` acts as a `dwarf2btf` converter. It doesn’t support `.BTF.ext` and btf `BTF_KIND_FUNC` type yet. See examples.

# References

* [Linux: 6. BTF Generation](https://www.kernel.org/doc/html/latest/bpf/btf.html)
