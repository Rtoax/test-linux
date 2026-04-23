# SPDX-License-Identifier: GPL-3.0
target-asm-y += hello
target-asm-y += hello-stack
target-asm-y += while
target-asm-y += out
target-asm-y += nanosleep

target-asm-std-y += average
target-asm-std-y += fibonacci
target-asm-std-y += power
target-asm-std-y += echo
target-asm-std-y += hola
target-asm-std-y += hello-puts

target-as-y += printf
target-as-y += putchar
target-as-y += read write
target-as-y += puts

target-y += factorial_call
target-y += maxofthree_call
#target-y += sum_call
target-y += hello-c
target-y += nanosleep-c
target-y += exit-c
target-y += write-c write-c-loop
target-y += out-c
target-y += puts-c puts-c-loop
target-y += atomic_forced_read
target-y += time
target-y += cr3

read-objs := syscall.S.o
exit-c-objs := exit.o
hello-c-objs := hello.o
nanosleep-c-objs := nanosleep.o
write-c-objs := write.o
write-c-loop-objs := write-loop.o
out-c-objs := out.o
puts-c-objs := puts.o
puts-c-loop-objs := puts-loop.o
factorial_call-objs := factorial.asm.o
maxofthree_call-objs := maxofthree.asm.o
sum_call-objs := sum.asm.o

ifneq ($(shell uname -m),x86_64)
  CC = x86_64-linux-gnu-gcc
  LD = x86_64-linux-gnu-ld
  RUN_PFX = qemu-x86_64
  LDFLAGS += --sysroot $(HOME)/rootfs-x86_64
endif

CFLAGS_write-loop := -DINFINITE_LOOP=1
CFLAGS_puts-loop := -DINFINITE_LOOP=1

ASMLDFLAGS += -z noexecstack

LDFLAGS_power += -no-pie
LDFLAGS_echo += -no-pie
LDFLAGS_hola += -no-pie
LDFLAGS_average += -no-pie
LDFLAGS_fibonacci += -no-pie
LDFLAGS_hello-puts += -no-pie
