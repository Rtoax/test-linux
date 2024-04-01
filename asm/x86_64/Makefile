CC = gcc
AS = as
LD = ld
OBJDUMP = objdump
RUN_PFX =
AS_ARGS :=
LD_ARGS :=

TARGETS :=

TARGETS_ld := hello
TARGETS_ld += hello-stack
TARGETS_ld += while
TARGETS_ld += nanosleep

# TODO
TARGETS_todo += sum_cal

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

ifneq ($(shell uname -m),x86_64)
	CC = x86_64-linux-gnu-gcc
	AS = x86_64-linux-gnu-as
	LD = x86_64-linux-gnu-ld
	OBJDUMP = x86_64-linux-gnu-objdump
	RUN_PFX = qemu-x86_64
else
	TARGETS += echo
	TARGETS += hello-puts
	TARGETS += hola
	TARGETS += fibonacci
	TARGETS += power
	TARGETS += factorial_call
	TARGETS += maxofthree_call
	TARGETS += hello-c
	TARGETS += atomic_forced_read
	TARGETS += time
endif

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS} ${TARGETS_ld}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
echo: echo.o
hello-puts: hello-puts.o
hello: hello.o
hello-c: hello-c.o
hello-stack: hello-stack.o
nanosleep: nanosleep.o
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
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	nasm -felf64 $(<) -o $(@)

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %.o:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

$(TARGETS_ld): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(LD) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_ld} *.o *.d core.* *.s
