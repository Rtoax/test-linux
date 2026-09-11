=====================
BTF (BPF Type Format)
=====================

BTF Types
---------

- `BTF_KIND_DECL_TAG`: Declaration Tag


Base BTF and Split BTF
----------------------

- `btf__parse()`: like vmlinux;
- `btf__parse_split()`: like kvm, etc;


/sys/kernel/btf/
----------------

* `/sys/kernel/btf/vmlinux`
	* `btf_vmlinux_init()`
	* `btf_vmlinux_read()`
* `/sys/kernel/btf/kvm`


pahole
------

Shows, manipulates data structure layout and pretty prints raw data.

* `pahole.git <https://git.kernel.org/pub/scm/devel/pahole/pahole.git/>`_

The `pahole` acts as a `dwarf2btf` converter. It doesn’t support `.BTF.ext`
and btf `BTF_KIND_FUNC` type yet. See examples.


References
----------

* `Linux: BTF Generation <https://www.kernel.org/doc/html/latest/bpf/btf.html>`_
