target-y := cpu_relax

subdir-${IS_AARCH64} += aarch64
subdir-${IS_LOONGARCH64} += loongarch64
subdir-${IS_PPC64LE} += ppc64le
subdir-${IS_RISCV64} += riscv64
subdir-${IS_S390X} += s390x
subdir-${IS_SW_64} += sw_64
subdir-${IS_X86_64} += x86_32
subdir-${IS_X86_64} += x86_64

post-y := $(patsubst %,${OUTPUT}%.c.s,${target-y})
