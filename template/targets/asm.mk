# SPDX-License-Identifier: GPL-3.0
#
# Assembler Types
# | Command | Type              | Grammar | Example      |
# | ------- | ----------------- | ------- | ------------ |
# | as      | GNU Assembler     | AT&T    | mov %ax, %bx |
# | nasm    | Netwide Assembler | Intel   | mov bx, ax   |
#
# Targets:
# - %.s.o
# - %.asm.o
# - target-as-y
# - target-asm-y
# - target-asm-std-y
#
ifndef _TARGET_ASM_MK
_TARGET_ASM_MK = 1

CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm

include cflags.mk

ifdef M32
  ASMFLAGS += -felf32
  ASMLDFLAGS += -m elf_i386
else
  ASMFLAGS += -felf64
endif

# M32: -felf32
${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_obj,NASM,$(@))
	${Q}${NASM} -o $(@) $(<) $(ASMFLAGS) $(ASMFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
${target-asm-y}: %:
	$(call log_tgt,LD ASM,$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))

$(target-asm-std-y): %:
	$(call log_tgt,LD ASM STD,$(@))
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

# Or use CC directly
${OUTPUT}%.s.o: %.s | ${OUTPUT}
	$(call log_obj,AS,$(@))
	${Q}${AS} -o $(@) $(<) $(ASFLAGS) $(ASFLAGS_$(*))

# Default _start() entry and link libc
${target-as-y}: %:
	$(call log_tgt,LD S,$(@))
	${Q}$(LD) -lc -o $(@) $(^) $(ASLDFLAGS) $(ASLDFLAGS_$(*))

# TODO: auto deps

endif
