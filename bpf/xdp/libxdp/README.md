libxdp
======

# Concept

libxdp is a light eBPF library who add 2 features for XDP programs.

- Load multiple programs on single network device using a "dispatcher program" thanks to [freplace](https://docs.ebpf.io/linux/program-type/BPF_PROG_TYPE_EXT/).
- Configuring `AF_XDP` and functions to read and write on theses sockets

You can check more information on the libxdp readme.


# Links

- https://docs.ebpf.io/ebpf-library/libxdp/libxdp/
- https://github.com/xdp-project/xdp-tools
