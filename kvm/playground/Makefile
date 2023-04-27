ARCH=$(shell uname -m)

ifeq (${ARCH},x86_64)
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

TARGETS += hello
TARGETS += basic-vm
TARGETS += load-payload01
TARGETS += load-payload02
TARGETS += cpuid
TARGETS += ia32e-paging
TARGETS += exceptions

all: ${TARGETS}
	@echo -e "\033[1;33mDone\033[m"

hello: hello.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(<)
	$(AS) hello.asm -o hello.o
	$(OBJCOPY) -O binary hello.o hello.bin

basic-vm: basic-vm.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(<)
	$(NASM) -felf64 -o basic-vm.o basic-vm.asm

load-payload01: load-payload01.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) load-payload01-program.asm -o load-payload01-program.bin
	$(NASM) -felf64 -o load-payload01-payload.o load-payload01-payload.asm
	$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<)

load-payload02: load-payload02.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) load-payload02-program.asm -o load-payload02-program.bin
	$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<)

cpuid: cpuid.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) cpuid-program.asm -o cpuid-program.bin
	$(NASM) -felf64 -o cpuid-payload.o cpuid-payload.asm
	$(CC) $(CFLAGS) -o $(@) cpuid-payload.o $(<)

ia32e-paging: ia32e-paging.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) -O0 ia32e-paging-a.asm -o ia32e-paging-a.bin
	$(NASM) -O0 ia32e-paging-b.asm -o ia32e-paging-b.bin
	$(CC) $(CFLAGS) -o $(@) $(<)

exceptions: exceptions.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) exceptions-a.asm -o exceptions-a.bin
	$(NASM) exceptions-handler.asm -o exceptions-handler.bin
	$(CC) $(CFLAGS) -o $(@) $(<)

clean:
	@echo -e "\033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.bin
