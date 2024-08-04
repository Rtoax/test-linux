SHELL = bash

CC = gcc
NASM = $(shell which nasm 2>/dev/null)
LD = ld
OBJDUMP = objdump
RUN_PFX =

TARGETS :=
TARGETS_S :=

ifneq ($(NASM),)
TARGETS_ASM := hello
TARGETS_ASM += hello-stack
TARGETS_ASM += while
TARGETS_ASM += nanosleep
endif

TARGETS_S += printf-main
TARGETS_S += read-main write-main

# TODO
TARGETS_todo += sum_cal

ifeq ($(shell uname -m),x86_64)
  TARGETS += cr3
endif
ifeq ($(shell uname -m),aarch64)
endif

ifneq ($(shell uname -m),x86_64)
  CC = x86_64-linux-gnu-gcc
  LD = x86_64-linux-gnu-ld
  OBJDUMP = x86_64-linux-gnu-objdump
  RUN_PFX = qemu-x86_64
else
  ifneq ($(NASM),)
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
    TARGETS += write-c
    TARGETS += atomic_forced_read
    TARGETS += time
  endif
endif

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS} ${TARGETS_S} ${TARGETS_ASM}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
cr3: cr3.o
echo: echo.o
hello-puts: hello-puts.o
hello: hello.o
hello-c: hello-c.o
nanosleep-c: nanosleep-c.o
exit-c: exit-c.o
write-c: write-c.o
hello-stack: hello-stack.o
nanosleep: nanosleep.o
printf-main: printf-main.o
read-main: read-main.o
write-main: write-main.o
fibonacci: fibonacci.o
hola: hola.o
sum_cal: sum_cal.o sum.o
factorial_call: factorial_call.o factorial.o
maxofthree_call: maxofthree_call.o maxofthree.o
power: power.o
while: while.o
atomic_forced_read: atomic_forced_read.o
time: time.o

%.o: %.asm
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(NASM) -felf64 $(<) -o $(@)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	@$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.S
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS) $(TARGETS_S): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

$(TARGETS_ASM): %:
	@echo -e "  LD  ld \033[1;32m$(@)\033[m"
	@$(LD) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} ${TARGETS_ASM} ${TARGETS_S} *.o *.d core.* *.s
