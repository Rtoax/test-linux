# SPDX-License-Identifier: GPL-3.0
RUN_PFX =

TARGETS_ASM := hello
TARGETS_ASM += hello-stack
TARGETS_ASM += while
TARGETS_ASM += out
TARGETS_ASM += nanosleep

TARGETS := printf-main
TARGETS += read-main write-main
TARGETS += puts-main
TARGETS += putchar-main

# TODO
TARGETS_todo += sum_cal

ifeq ($(shell uname -m),x86_64)
  TARGETS += cr3
endif

ifneq ($(shell uname -m),x86_64)
  CC = x86_64-linux-gnu-gcc
  LD = x86_64-linux-gnu-ld
  RUN_PFX = qemu-x86_64
  LDFLAGS += --sysroot /home/rongtao/rootfs-x86_64
else
  TARGETS += echo
  TARGETS += hello-puts
  TARGETS += hola
  TARGETS += fibonacci
  TARGETS += power
  TARGETS += factorial_call
  TARGETS += maxofthree_call
  TARGETS += hello-c
  TARGETS += nanosleep-c
  TARGETS += exit-c
  TARGETS += write-c write-c-loop
  TARGETS += out-c
  TARGETS += puts-c puts-c-loop
  TARGETS += atomic_forced_read
  TARGETS += time
endif

CFLAGS_write-c-loop := -DINFINITE_LOOP=1
CFLAGS_puts-c-loop := -DINFINITE_LOOP=1

NOPIE ?= 1
include ../../../elf/pie.mk

LDFLAGS += -z noexecstack

include ../../../template/main.mk

cr3: cr3.o
echo: echo.asm.o
hello-puts: hello-puts.asm.o
hello: hello.asm.o
hello-c: hello-c.o
nanosleep-c: nanosleep-c.o
exit-c: exit-c.o
write-c: write-c.o
write-c-loop: write-c-loop.o
out-c: out-c.o
puts-c: puts-c.o
puts-c-loop: puts-c-loop.o
hello-stack: hello-stack.asm.o
nanosleep: nanosleep.asm.o
printf-main: printf-main.S.o
read-main: read-main.S.o
write-main: write-main.S.o
puts-main: puts-main.S.o
putchar-main: putchar-main.S.o
fibonacci: fibonacci.asm.o
hola: hola.asm.o
sum_cal: sum_cal.o sum.o
factorial_call: factorial_call.o factorial.asm.o
maxofthree_call: maxofthree_call.o maxofthree.asm.o
power: power.asm.o
while: while.asm.o
out: out.asm.o
atomic_forced_read: atomic_forced_read.o
time: time.o

test0: ${TARGETS}
	$(call log_tgt_exe,TEST,,$(@))
	$(Q)$(RUN_PFX) ./hello
