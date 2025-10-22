OUTPUT := .output/
CC := gcc
NASM := nasm

# Include '_start' function
target-asm-y += call-func call-func-ret
target-asm-y += jmp jg jl
target-asm-y += write write-2 write-3

define m32_build
  $(shell $(NASM) average.asm -felf32 -o a.o && \
	  $(CC) -Wall -m32 a.o -o /dev/null >/dev/null 2>&1 \
      && echo y)
endef
nasm-m32 := $(findstring y,$(call m32_build,))

# Include 'main' function
ifeq ($(nasm-m32),y)
  target-y += average
  target-y += echo
  target-y += power
  target-y += factorial_call
  target-y += maxofthree_call
else
  $(warning "WARNING: Not support 32bit")
endif

CFLAGS += -m32
LDFLAGS += -m32
ASMCFLAGS += -felf32
ASMLDFLAGS += -m elf_i386

include ../../../template/main.mk

average: ${OUTPUT}average.asm.o
echo: ${OUTPUT}echo.asm.o
call-func: ${OUTPUT}call-func.asm.o
call-func-ret: ${OUTPUT}call-func-ret.asm.o
jmp: ${OUTPUT}jmp.asm.o
jg: ${OUTPUT}jg.asm.o
jl: ${OUTPUT}jl.asm.o
power: ${OUTPUT}power.asm.o
write: ${OUTPUT}write.asm.o
write-2: ${OUTPUT}write-2.asm.o
write-3: ${OUTPUT}write-3.asm.o
factorial_call: ${OUTPUT}factorial_call.o ${OUTPUT}factorial.asm.o
maxofthree_call: ${OUTPUT}maxofthree_call.o ${OUTPUT}maxofthree.asm.o
