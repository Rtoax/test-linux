SHELL = bash

CC = gcc
LD = ld
AS = nasm

# Check compiler support -m32 or not
define m32_build
  $(shell $(AS) average.asm -felf32 -o a.o && \
	  $(CC) -Wall -m32 a.o -o - >/dev/null 2>&1 \
      && echo 1)
endef
feature-m32 := $(findstring 1,$(call m32_build,))
#$(info FEATURE m32: ${feature-m32})

# Include '_start' function
TARGETS :=
TARGETS += call-func call-func-ret
TARGETS += jmp jg jl
TARGETS += write write-2 write-3

# Include 'main' function
TARGETS_MAIN :=
ifeq ($(feature-m32),1)
TARGETS_MAIN += average
TARGETS_MAIN += echo
TARGETS_MAIN += power
TARGETS_MAIN += factorial_call
TARGETS_MAIN += maxofthree_call
else
$(warning "WARNING: Not support 32bit")
endif

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

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(LD) -m elf_i386 -o $(@) $(^)

$(TARGETS_MAIN): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -m32 -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./echo Hello World
	./average 1 2 3 4

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	# FIXME: Gcc on fedora40 '-o -' generate '-'
	@rm -f ${TARGETS} ${TARGETS_MAIN} *.o *.d *.oc -
