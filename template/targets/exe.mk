# SPDX-License-Identifier: GPL-3.0
_TARGET_EXE = 1

CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm
CC_PFX :=

${OUTPUT}%.o: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.E.c: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC E,$(<),$(@))
	${Q}${CC_PFX} $(CC) -E -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC S,$(<),$(@))
	${Q}${CC_PFX} $(CC) -S -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	$(call log_tgt_obj,CXX,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	$(call log_tgt_obj,CXX S,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -S -o $(@) $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_tgt_obj,ASM,$(<),$(@))
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMCFLAGS) $(ASMCFLAGS_$(*))

${OUTPUT}%.as.o: %.asm | ${OUTPUT}
	$(call log_tgt_obj,AS,$(<),$(@))
	${Q}${AS} -o $(@) $(<) $(ASCFLAGS) $(ASCFLAGS_$(*))

# Same as: as {--64,--32} a.S -o a.o
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	$(call log_tgt_obj,CC S,$(<),$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(targets): %:
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${targets-cpp}: %:
	$(call log_tgt_exe,LD CXX,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
${targets-asm}: %:
	$(call log_tgt_exe,LD ASM,$(<),$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))
