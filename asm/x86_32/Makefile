
TARGETS := call-func call-func-ret
TARGETS += jmp jg jl
TARGETS += write write-2

TARGETS_gcc := factorial_call

TARGETS_todo := echo
ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -m32

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS} ${TARGETS_gcc}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
echo: echo.o
call-func: call-func.o
call-func-ret: call-func-ret.o
jmp: jmp.o
jg: jg.o
jl: jl.o
write: write.o
write-2: write-2.o
factorial_call: factorial_call.o factorial.o

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	nasm -felf32 $(<) -o $(@)

$(TARGETS): %.o:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	ld -m elf_i386 -o $(@) $(^)

$(TARGETS_gcc): %.o:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	gcc -m32 -o $(@) $(^)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./echo Hello World

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_gcc} *.o *.d
