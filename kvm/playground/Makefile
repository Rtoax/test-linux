DEBUG = yes
CC = gcc
NASM = nasm

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

TARGETS += basic-vm
TARGETS += load-payload01

all: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

basic-vm: basic-vm.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(<)
	$(NASM) -felf64 -o basic-vm.o basic-vm.asm

load-payload01: load-payload01.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(NASM) load-payload01-program.asm -o load-payload01-program.bin
	$(NASM) -felf64 -o load-payload01-payload.o load-payload01-payload.asm
	$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<)

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.bin
