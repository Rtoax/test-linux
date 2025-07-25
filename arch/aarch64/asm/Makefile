CC := gcc
AS := as
LD := ld
LDFLAGS :=

targets :=

targets-asm := hello
targets-asm += hello-stack
targets-asm += paciasp
targets-asm += exit
targets-asm += ldr
targets-asm += while
targets-asm += add
targets-asm += mov
targets-asm += nanosleep

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
  targets-asm += hello_sve
  targets += daxpy
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
  targets += add-c
  targets += loop-c
  targets += puts
  targets += paciasp-c
  targets += nanosleep-c
  targets += write-c write-c-loop
  targets += exit-c

  targets-asm += branch

  targets += main
  targets += say_hello
  targets += hello-puts
  targets += hello-puts-infinite-loop
  targets += hello-main
  targets += read-main
  targets += exit-main
  targets += puts-main
  targets += printf-main

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
  targets-asm := $(filter-out branch, $(targets-asm))
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
