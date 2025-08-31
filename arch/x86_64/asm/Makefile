# SPDX-License-Identifier: GPL-3.0
RUN_PFX =

targets-asm := hello
targets-asm += hello-stack
targets-asm += while
targets-asm += out
targets-asm += nanosleep

targets := printf-main
targets += read-main write-main
targets += puts-main
targets += putchar-main

# TODO
targets-todo += sum_cal

ifeq ($(shell uname -m),x86_64)
  targets += cr3
endif

ifneq ($(shell uname -m),x86_64)
  CC = x86_64-linux-gnu-gcc
  LD = x86_64-linux-gnu-ld
  RUN_PFX = qemu-x86_64
  LDFLAGS += --sysroot /home/rongtao/rootfs-x86_64
else
  targets += echo
  targets += hello-puts
  targets += hola
  targets += fibonacci
  targets += power
  targets += factorial_call
  targets += maxofthree_call
  targets += hello-c
  targets += nanosleep-c
  targets += exit-c
  targets += write-c write-c-loop
  targets += out-c
  targets += puts-c puts-c-loop
  targets += atomic_forced_read
  targets += time
endif

CFLAGS_write-c-loop := -DINFINITE_LOOP=1
CFLAGS_puts-c-loop := -DINFINITE_LOOP=1

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

test0: ${targets}
	$(call log_tgt_exe,TEST,,$(@))
	$(Q)$(RUN_PFX) ./hello
