# SPDX-License-Identifier: GPL-3.0
#
# Assembler Types
# | Command | Type              | Grammar | Example      |
# | ------- | ----------------- | ------- | ------------ |
# | as      | GNU Assembler     | AT&T    | mov %ax, %bx |
# | nasm    | Netwide Assembler | Intel   | mov bx, ax   |
#
# Targets:
# - %.asm.o
# - %.s.o
# - target-as-y
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
	$(call log_obj,ASM,$(@))
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMCFLAGS) $(ASMCFLAGS_$(*))

${OUTPUT}%.s.o: %.s | ${OUTPUT}
	$(call log_obj,AS,$(@))
	${Q}${AS} -o $(@) $(<) $(ASFLAGS) $(ASFLAGS_$(*))

# Default _start() entry and link libc
${target-as-y}: %:
	$(call log_tgt,LD S,$(@))
	${Q}$(LD) -lc -o $(@) $(^) $(ASLDFLAGS) $(ASLDFLAGS_$(*))

# Same as: as {--64,--32} a.S -o a.o
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	$(call log_obj,CC S,$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
# TODO: auto deps
${target-asm-y}: %:
	$(call log_tgt,LD ASM,$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))

endif
