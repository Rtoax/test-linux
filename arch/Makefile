include arch.mk

target-y := cpu_relax

subdir-${IS_X86_64} += x86_32
subdir-${IS_X86_64} += x86_64
subdir-${IS_AARCH64} += aarch64
subdir-${IS_SW_64} += sw_64
subdir-${IS_LOONGARCH64} += loongarch64
subdir-${IS_RISCV64} += riscv64

target-post-y := $(patsubst %,%.c.s,${target-y})

include main.mk

cpu_relax: cpu_relax.o
