# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_EXE_MK
_TARGET_EXE_MK = 1

CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm

${OUTPUT}%.o: %.c | ${OUTPUT}
	$(call log_obj,CC,$(<),$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.E.c: %.c | ${OUTPUT}
	$(call log_obj,CC E,$(<),$(@))
	${Q}$(CC) -E -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	$(call log_obj,CC S,$(<),$(@))
	${Q}$(CC) -S -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	$(call log_obj,CXX,$(<),$(@))
	${Q}$(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	$(call log_obj,CXX S,$(<),$(@))
	${Q}$(CXX) -S -o $(@) $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

# Better define OUTPUT, to fix make: Circular dependency
${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_obj,ASM,$(<),$(@))
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMCFLAGS) $(ASMCFLAGS_$(*))

${OUTPUT}%.as.o: %.asm | ${OUTPUT}
	$(call log_obj,AS,$(<),$(@))
	${Q}${AS} -o $(@) $(<) $(ASCFLAGS) $(ASCFLAGS_$(*))

# Same as: as {--64,--32} a.S -o a.o
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	$(call log_obj,CC S,$(<),$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(target-y): %:
	$(call log_exe,LD,$(<),$(@))
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${target-cpp-y}: %:
	$(call log_exe,LD CXX,$(<),$(@))
	${Q}$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
${target-asm-y}: %:
	$(call log_exe,LD ASM,$(<),$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))

endif
