target-asm-y := hello
target-asm-y += hello-stack
target-asm-y += paciasp
target-asm-y += exit
target-asm-y += ldr
target-asm-y += while
target-asm-y += add
target-asm-y += mov
target-asm-y += nanosleep

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
  target-y += loop-c
  target-y += puts-c
  target-y += paciasp-c
  target-y += nanosleep-c
  target-y += write-c write-c-loop
  target-y += exit-c

  target-asm-y += branch

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

puts-c-objs := puts.o

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
CFLAGS_paciasp-c := -march=armv8.3-a

ASFLAGS_hello-puts-infinite-loop := -DINFINITE_LOOP=1
CFLAGS_write-c-loop := -DINFINITE_LOOP=1

include main.mk

add: add.s.o
branch: branch.s.o
hello: hello.s.o
hello-stack: hello-stack.s.o
paciasp: paciasp.s.o
hello-puts: hello-puts.s.o
hello-puts-infinite-loop: hello-puts-infinite-loop.s.o
main: main.s.o
read: read.s.o
puts: puts.s.o
printf: printf.s.o
say_hello: say_hello.s.o
exit: exit.s.o
nanosleep: nanosleep.s.o
hello_sve: hello_sve.s.o
daxpy: daxpy.s.o daxpy_sve.s.o daxpy-c.o
while: while.s.o
ldr: ldr.s.o
mov: mov.s.o
