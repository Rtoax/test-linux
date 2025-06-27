CC := gcc
NASM := nasm

# Include '_start' function
TARGETS_ASM += call-func call-func-ret
TARGETS_ASM += jmp jg jl
TARGETS_ASM += write write-2 write-3

define m32_build
  $(shell $(NASM) average.asm -felf32 -o a.o && \
	  $(CC) -Wall -m32 a.o -o /dev/null >/dev/null 2>&1 \
      && echo 1)
endef
feature-m32 := $(findstring 1,$(call m32_build,))

# Include 'main' function
ifeq ($(feature-m32),1)
  TARGETS += average
  TARGETS += echo
  TARGETS += power
  TARGETS += factorial_call
  TARGETS += maxofthree_call
else
  $(warning "WARNING: Not support 32bit")
endif

CFLAGS += -m32
LDFLAGS += -m32
ASMCFLAGS += -felf32
ASMLDFLAGS += -m elf_i386

include ../../../template/main.mk

average: average.asm.o
echo: echo.asm.o
call-func: call-func.asm.o
call-func-ret: call-func-ret.asm.o
jmp: jmp.asm.o
jg: jg.asm.o
jl: jl.asm.o
power: power.asm.o
write: write.asm.o
write-2: write-2.asm.o
write-3: write-3.asm.o
factorial_call: factorial_call.o factorial.asm.o
maxofthree_call: maxofthree_call.o maxofthree.asm.o
