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
#
ifndef _TARGET_ASM_MK
_TARGET_ASM_MK = 1

CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm

include cflags.mk

# Better define OUTPUT, to fix make: Circular dependency
${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_obj,NASM,$(@))
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMFLAGS) $(ASMFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
${target-asm-y}: %:
	$(call log_tgt,LD ASM,$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))

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
