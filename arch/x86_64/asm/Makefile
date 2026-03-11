# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-asm-y := hello
target-asm-y += hello-stack
target-asm-y += while
target-asm-y += out
target-asm-y += nanosleep

target-as-y += printf
target-as-y += putchar
target-as-y += read write
target-as-y += puts

target-y += echo
target-y += hello-puts
target-y += hola
target-y += fibonacci
target-y += power
target-y += factorial_call
target-y += maxofthree_call
target-y += hello-c
target-y += nanosleep-c
target-y += exit-c
target-y += write-c write-c-loop
target-y += out-c
target-y += puts-c puts-c-loop
target-y += atomic_forced_read
target-y += time
target-y += cr3

# TODO
target-todo += sum_cal

exit-c-objs := ${OUTPUT}exit.o
hello-c-objs := ${OUTPUT}hello.o
nanosleep-c-objs := ${OUTPUT}nanosleep.o
write-c-objs := ${OUTPUT}write.o
write-c-loop-objs := ${OUTPUT}write-loop.o
out-c-objs := ${OUTPUT}out.o
puts-c-objs := ${OUTPUT}puts.o
puts-c-loop-objs := ${OUTPUT}puts-loop.o

ifneq ($(shell uname -m),x86_64)
  CC = x86_64-linux-gnu-gcc
  LD = x86_64-linux-gnu-ld
  RUN_PFX = qemu-x86_64
  LDFLAGS += --sysroot $(HOME)/rootfs-x86_64
endif

CFLAGS_write-loop := -DINFINITE_LOOP=1
CFLAGS_puts-loop := -DINFINITE_LOOP=1

LDFLAGS += -z noexecstack
LDFLAGS_echo += -no-pie
LDFLAGS_hello-puts += -no-pie
LDFLAGS_hola += -no-pie
LDFLAGS_fibonacci += -no-pie
LDFLAGS_power += -no-pie

include main.mk

cr3: ${OUTPUT}cr3.o
echo: ${OUTPUT}echo.asm.o
hello-puts: ${OUTPUT}hello-puts.asm.o
hello: ${OUTPUT}hello.asm.o
hello-stack: ${OUTPUT}hello-stack.asm.o
nanosleep: ${OUTPUT}nanosleep.asm.o
printf: ${OUTPUT}printf.s.o
read: ${OUTPUT}read.s.o
write: ${OUTPUT}write.s.o
puts: ${OUTPUT}puts.s.o
putchar: ${OUTPUT}putchar.s.o
fibonacci: ${OUTPUT}fibonacci.asm.o
hola: ${OUTPUT}hola.asm.o
sum_cal: ${OUTPUT}sum_cal.o ${OUTPUT}sum.o
factorial_call: ${OUTPUT}factorial_call.o ${OUTPUT}factorial.asm.o
maxofthree_call: ${OUTPUT}maxofthree_call.o ${OUTPUT}maxofthree.asm.o
power: ${OUTPUT}power.asm.o
while: ${OUTPUT}while.asm.o
out: ${OUTPUT}out.asm.o
atomic_forced_read: ${OUTPUT}atomic_forced_read.o
time: ${OUTPUT}time.o

test0: ${target-y}
	$(call log_tgt,TEST,$(@))
	$(Q)$(RUN_PFX) ./hello
