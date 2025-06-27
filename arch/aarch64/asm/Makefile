CC := gcc
AS := as
LD := ld
LDFLAGS :=

TARGETS :=

TARGETS_ASM := hello
TARGETS_ASM += hello-stack
TARGETS_ASM += paciasp
TARGETS_ASM += exit
TARGETS_ASM += ldr
TARGETS_ASM += while
TARGETS_ASM += add
TARGETS_ASM += mov
TARGETS_ASM += nanosleep

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
  TARGETS_ASM += hello_sve
  TARGETS += daxpy
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
  TARGETS += add-c
  TARGETS += loop-c
  TARGETS += puts
  TARGETS += paciasp-c
  TARGETS += nanosleep-c
  TARGETS += write-c write-c-loop
  TARGETS += exit-c

  TARGETS_ASM += branch

  TARGETS += main
  TARGETS += say_hello
  TARGETS += hello-puts
  TARGETS += hello-puts-infinite-loop
  TARGETS += hello-main
  TARGETS += read-main
  TARGETS += exit-main
  TARGETS += puts-main
  TARGETS += printf-main

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
  TARGETS_ASM := $(filter-out branch, $(TARGETS_ASM))
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
