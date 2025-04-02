vmalloc
=======


# vmalloc=nn[KMG]

Forces the vmalloc area to have an exact size of <nn>. This can be used to increase the minimum size (128MB on x86, arm32 platforms). It can also be used to decrease the size and leave more room for directly mapped kernel RAM. Note that this parameter does not exist on many other platforms (including arm64, alpha, loongarch, arc, csky, hexagon, microblaze, mips, nios2, openrisc, parisc, m64k, powerpc, riscv, sh, um, xtensa, s390, sparc).


# Links

- https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
