sub-dir := Rescheduling-interrupts

x86 := cli

ifeq ($(shell uname -m),x86_64)
  target-y := ${x86}
endif

include ../template/main.mk

cli: cli.o
