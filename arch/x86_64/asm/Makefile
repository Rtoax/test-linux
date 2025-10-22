# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

RUN_PFX =

target-asm-y := hello
target-asm-y += hello-stack
target-asm-y += while
target-asm-y += out
target-asm-y += nanosleep

target-y := printf-main
target-y += read-main write-main
target-y += puts-main
target-y += putchar-main

# TODO
target-todo += sum_cal

ifeq ($(shell uname -m),x86_64)
  target-y += cr3
endif

ifneq ($(shell uname -m),x86_64)
  CC = x86_64-linux-gnu-gcc
  LD = x86_64-linux-gnu-ld
  RUN_PFX = qemu-x86_64
  LDFLAGS += --sysroot /home/rongtao/rootfs-x86_64
else
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
endif

CFLAGS_write-c-loop := -DINFINITE_LOOP=1
CFLAGS_puts-c-loop := -DINFINITE_LOOP=1

LDFLAGS += -z noexecstack

include ../../../template/main.mk

cr3: ${OUTPUT}cr3.o
echo: ${OUTPUT}echo.asm.o
hello-puts: ${OUTPUT}hello-puts.asm.o
hello: ${OUTPUT}hello.asm.o
hello-c: ${OUTPUT}hello-c.o
nanosleep-c: ${OUTPUT}nanosleep-c.o
exit-c: ${OUTPUT}exit-c.o
write-c: ${OUTPUT}write-c.o
write-c-loop: ${OUTPUT}write-c-loop.o
out-c: ${OUTPUT}out-c.o
puts-c: ${OUTPUT}puts-c.o
puts-c-loop: ${OUTPUT}puts-c-loop.o
hello-stack: ${OUTPUT}hello-stack.asm.o
nanosleep: ${OUTPUT}nanosleep.asm.o
printf-main: ${OUTPUT}printf-main.S.o
read-main: ${OUTPUT}read-main.S.o
write-main: ${OUTPUT}write-main.S.o
puts-main: ${OUTPUT}puts-main.S.o
putchar-main: ${OUTPUT}putchar-main.S.o
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
	$(call log_tgt_exe,TEST,,$(@))
	$(Q)$(RUN_PFX) ./hello
