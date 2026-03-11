target-asm-y := hello
target-asm-y += hello-stack
target-asm-y += ldr
target-asm-y += while
target-asm-y += nanosleep
target-asm-y += mov

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
  target-asm-y += hello_sve
  target-y += daxpy
  ASFLAGS := -march=armv8-a+sve2
endif

# Cross compile
# If cross compile, you could use binfmt_misc to running aarch64 on x86_64, ..
ifneq ($(shell uname -m),aarch64)
  include cross-compile.mk
  CC := aarch64-linux-gnu-gcc
  AS := aarch64-linux-gnu-as
  LD := aarch64-linux-gnu-ld
  OBJDUMP := aarch64-linux-gnu-objdump
  RUN_PFX := qemu-aarch64
  ASMLDFLAGS += --sysroot $(HOME)/rootfs-aarch64/
else ifeq ($(shell uname -m),aarch64)
  target-y += add-c
  target-y += loop
  target-y += puts-c
  target-y += paciasp-c
  target-y += nanosleep-c
  target-y += write write-loop
  target-y += exit-c

  target-asm-y += branch

  target-as-y += add
  target-as-y += say_hello
  target-as-y += read
  target-as-y += hello-puts
  target-as-y += hello-puts-infinite-loop
  target-as-y += puts
  target-as-y += main
  target-as-y += printf

  LDFLAGS += -lc

  ASMLDFLAGS += -lc
endif

add-c-objs := add.o
exit-c-objs := exit.o
puts-c-objs := puts.o
paciasp-c-objs := paciasp.o
nanosleep-c-objs := nanosleep.o
daxpy-objs := daxpy.s.o daxpy_sve.s.o

ifdef STATIC
  CFLAGS += -static
  # Remove -lc
  LDFLAGS :=
  LDFLAGS += -static
  # FIXME: branch.asm no main() but call libc::printf(), I try 'gcc -nostdlib'
  # but it not works.
  target-asm-y := $(filter-out branch, $(target-asm-y))
endif

ASFLAGS_paciasp := -march=armv8.3-a
CFLAGS_paciasp := -march=armv8.3-a

ASFLAGS_hello-puts-infinite-loop := -DINFINITE_LOOP=1
CFLAGS_write-loop := -DINFINITE_LOOP=1

include main.mk
