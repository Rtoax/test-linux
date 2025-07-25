sub-dir :=

targets := cpu_relax
ifeq ($(shell uname -m),x86_64)
  sub-dir += x86_32
  sub-dir += x86_64
else ifeq ($(shell uname -m),aarch64)
  sub-dir += aarch64
else ifeq ($(shell uname -m),sw_64)
  sub-dir += sw_64
else ifeq ($(shell uname -m),loongarch64)
  sub-dir += loongarch64
else ifeq ($(shell uname -m),riscv64)
  sub-dir += riscv64
endif

targets-post := $(patsubst %,%.c.s,${targets})

include ../template/main.mk

cpu_relax: cpu_relax.o
