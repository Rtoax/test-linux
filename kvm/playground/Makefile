DEBUG = yes
CC = gcc
NASM = nasm

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

TARGETS += basic-vm

basic-vm: basic-vm.c
	@echo -e "\033[1;33m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(<)
	$(NASM) -felf64 -o basic-vm.o basic-vm.asm

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.bin
