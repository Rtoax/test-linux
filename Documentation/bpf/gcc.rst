======================================
BPF Support in the GNU Toolchain (GCC)
======================================

Compiler
--------

The GCC compiler comes with an eBPF backend starting from **GCC 10**. Up to
that point, LLVM has been the only compiler which supports generating eBPF
ELF files.


Distro availability
~~~~~~~~~~~~~~~~~~~

- Oracle: Linux cross-gcc, cross-binutils
- Debian: gcc-bpf, binutils-bpf
- Gentoo: sys-devel/bpf-toolchain
- Fedora: cross-gcc, cross-binutils


Links
-----

- `LWN: Compiling to BPF with GCC <https://lwn.net/Articles/800606/>`_
- `PDF: BPF Support in the GNU Toolchain <https://lpc.events/event/18/contributions/1924/attachments/1563/3251/lpc2024_bpf_toolchain.pdf>`_
- https://gcc.gnu.org/wiki/BPFBackEnd
- https://git.sr.ht/~brianwitte/gcc-bpf-example
    - github fork: https://github.com/Rtoax/gcc-bpf-example
    - gitee fork: https://gitee.com/rtoax/gcc-bpf-example
