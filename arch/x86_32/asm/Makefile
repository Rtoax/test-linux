GLIBC_M32_CRT1_O = /usr/lib/crt1.o

# Include '_start' function
TARGETS :=
TARGETS += call-func call-func-ret
TARGETS += jmp jg jl
TARGETS += write write-2 write-3

# Include 'main' function
TARGETS_MAIN :=
ifneq ($(wildcard $(GLIBC_M32_CRT1_O)),)
TARGETS_MAIN += average
TARGETS_MAIN += echo
TARGETS_MAIN += power
TARGETS_MAIN += factorial_call
TARGETS_MAIN += maxofthree_call
else
$(warning "WARNING: Not install glibc m32 development package")
endif

CC = gcc
LD = ld
AS = nasm

CFLAGS := -Werror -Wall
CFLAGS += -m32
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS} ${TARGETS_MAIN}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
average: average.o
echo: echo.o
call-func: call-func.o
call-func-ret: call-func-ret.o
jmp: jmp.o
jg: jg.o
jl: jl.o
power: power.o
write: write.o
write-2: write-2.o
write-3: write-3.o
factorial_call: factorial_call.oc factorial.o
maxofthree_call: maxofthree_call.oc maxofthree.o

%.o: %.asm
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(AS) -felf32 $(<) -o $(@)

%.oc: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -m32 -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %.o:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(LD) -m elf_i386 -o $(@) $(^)

$(TARGETS_MAIN): %.o:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -m32 -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./echo Hello World
	./average 1 2 3 4

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} ${TARGETS_MAIN} *.o *.d *.oc
