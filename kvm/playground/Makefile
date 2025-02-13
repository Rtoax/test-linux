include ../../tlbuild.mk


ARCH=$(shell uname -m)

TARGETS :=
LIBS :=

ifeq (${ARCH},x86_64)
TARGETS += hello
TARGETS += basic-vm
TARGETS += load-payload01
TARGETS += load-payload02
TARGETS += cpuid
TARGETS += assemly-compiling
TARGETS += ia32e-paging
TARGETS += protected-mode-with-paging
TARGETS += exceptions
endif

ifeq (${ARCH},aarch64)
endif

DEBUG = yes

CC = gcc
AS = as
NASM = nasm
OBJCOPY = objcopy

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

LIBS += common.o

all: ${TARGETS}
	@echo -e "\033[1;33mDone\033[m"

hello: hello.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)
	$(AS) hello.asm -o hello.o
	$(OBJCOPY) -O binary hello.o hello.bin

basic-vm: basic-vm.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

load-payload01: load-payload01.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) load-payload01-program.asm -o load-payload01-program.bin
	$(NASM) -felf64 -o load-payload01-payload.o load-payload01-payload.asm
	${Q}$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<) $(LIBS)

load-payload02: load-payload02.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) load-payload02-program.asm -o load-payload02-program.bin
	${Q}$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<) $(LIBS)

cpuid: cpuid.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) cpuid-program.asm -o cpuid-program.bin
	$(NASM) -felf64 -o cpuid-payload.o cpuid-payload.asm
	${Q}$(CC) $(CFLAGS) -o $(@) cpuid-payload.o $(<) $(LIBS)

assemly-compiling:
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) a16.asm -o a16.bin
	$(NASM) a32.asm -o a32.bin
	$(NASM) -O0 a64.asm -o a64.bin

ia32e-paging: ia32e-paging.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) -O0 ia32e-paging-a.asm -o ia32e-paging-a.bin
	$(NASM) -O0 ia32e-paging-b.asm -o ia32e-paging-b.bin
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

protected-mode-with-paging: protected-mode-with-paging.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) protected-mode-with-paging-a.asm -o protected-mode-with-paging-a.bin
	$(NASM) protected-mode-with-paging-b.asm -o protected-mode-with-paging-b.bin
	$(NASM) protected-mode-with-paging-c.asm -o protected-mode-with-paging-c.bin
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

exceptions: exceptions.c common.o
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) exceptions-a.asm -o exceptions-a.bin
	$(NASM) exceptions-handler.asm -o exceptions-handler.bin
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

clean:
	@echo -e "\033[1;32m$(@)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.bin
