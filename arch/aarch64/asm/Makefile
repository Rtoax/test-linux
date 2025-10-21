CC := gcc
AS := as
LD := ld
LDFLAGS :=

target-y :=

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
  ASCFLAGS := -march=armv8-a+sve2
endif

# Cross compile
# If cross compile, you could use binfmt_misc to running aarch64 on x86_64, ..
ifneq ($(shell uname -m),aarch64)
  include ../../../compiler/cross-compile.mk
  CC := aarch64-linux-gnu-gcc
  AS := aarch64-linux-gnu-as
  LD := aarch64-linux-gnu-ld
  OBJDUMP := aarch64-linux-gnu-objdump
  RUN_PFX := qemu-aarch64
  ASMLDFLAGS += --sysroot /home/rongtao/rootfs-aarch64/
else ifeq ($(shell uname -m),aarch64)
  target-y += add-c
  target-y += loop-c
  target-y += puts
  target-y += paciasp-c
  target-y += nanosleep-c
  target-y += write-c write-c-loop
  target-y += exit-c

  target-asm-y += branch

  target-y += main
  target-y += say_hello
  target-y += hello-puts
  target-y += hello-puts-infinite-loop
  target-y += hello-main
  target-y += read-main
  target-y += exit-main
  target-y += puts-main
  target-y += printf-main

  LDFLAGS += -lc

  ASMLDFLAGS += -lc
endif

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

CFLAGS_hello-puts-infinite-loop := -DINFINITE_LOOP=1
CFLAGS_write-c-loop := -DINFINITE_LOOP=1

include ../../../template/main.mk

add: add.as.o
branch: branch.as.o
hello: hello.as.o
hello-stack: hello-stack.as.o
paciasp: paciasp.as.o
hello-puts: hello-puts.o
hello-puts-infinite-loop: hello-puts-infinite-loop.o
main: main.o
hello-main: hello-main.o
read-main: read-main.o
exit-main: exit-main.o
puts-main: puts-main.o
printf-main: printf-main.o
say_hello: say_hello.o
exit: exit.as.o
nanosleep: nanosleep.as.o
hello_sve: hello_sve.o
daxpy: daxpy.o daxpy_sve.o daxpy-c.co
add-c: add-c.o
loop-c: loop-c.o
paciasp-c: paciasp-c.o
nanosleep-c: nanosleep-c.o
write-c: write-c.o
write-c-loop: write-c-loop.o
exit-c: exit-c.o
puts: puts.o
while: while.as.o
ldr: ldr.as.o
mov: mov.as.o
