sub-dir := Rescheduling-interrupts

targets-x86 := cli

ifeq ($(shell uname -m),x86_64)
  targets := ${targets-x86}
endif

include ../template/main.mk

cli: cli.o
