libbpf
======

Libbpf is the reference library for eBPF development. It is developed and maintained as part of the kernel tree often in lockstep with the kernel itself. Since including the whole kernel tree in a project is not practical, a mirror of just the libbpf library is maintained at https://github.com/libbpf/libbpf.

Libbpf has both userspace components and eBPF components. The eBPF components are mostly pre-processor statements, forward declarations and type definitions that make it easier to write eBPF programs. The userspace components is a library that for loading eBPF programs and interacting with the loaded resources.


# TODO

- [error-inject](https://github.com/eunomia-bpf/bpftime/tree/master/example/error-inject)


# Links

- https://docs.ebpf.io/ebpf-library/libbpf/
- https://github.com/libbpf/libbpf
- https://github.com/libbpf/blazesym

