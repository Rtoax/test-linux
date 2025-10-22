subdir-y :=

target-y := cpu_relax
ifeq ($(shell uname -m),x86_64)
  subdir-y += x86_32
  subdir-y += x86_64
else ifeq ($(shell uname -m),aarch64)
  subdir-y += aarch64
else ifeq ($(shell uname -m),sw_64)
  subdir-y += sw_64
else ifeq ($(shell uname -m),loongarch64)
  subdir-y += loongarch64
else ifeq ($(shell uname -m),riscv64)
  subdir-y += riscv64
endif

target-post-y := $(patsubst %,%.c.s,${target-y})

include ../template/main.mk

cpu_relax: cpu_relax.o
