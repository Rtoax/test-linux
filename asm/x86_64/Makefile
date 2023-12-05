
TARGETS := echo
TARGETS += hello-puts
TARGETS += hola
TARGETS += fibonacci
TARGETS += power
TARGETS += factorial_call
TARGETS += maxofthree_call

TARGETS_ld := hello
TARGETS_ld += hello-stack

# TODO
TARGETS_todo += sum_cal

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
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
hello-stack: hello-stack.o
fibonacci: fibonacci.o
hola: hola.o
sum_cal: sum_cal.o sum.o
factorial_call: factorial_call.o factorial.o
maxofthree_call: maxofthree_call.o maxofthree.o
power: power.o

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	nasm -felf64 $(<) -o $(@)

$(TARGETS): %.o:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

$(TARGETS_ld): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	ld -o $(@) $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./echo Hello World

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_ld} *.o *.d core.*
