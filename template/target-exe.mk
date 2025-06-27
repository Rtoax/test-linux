# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm
CC_PFX := LD_LIBRARY_PATH=$(shell pwd)

${OUTPUT}%.o: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC S,$(<),$(@))
	${Q}${CC_PFX} $(CC) -S -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	$(call log_tgt_obj,CXX,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	$(call log_tgt_obj,CXX S,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -S -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_tgt_obj,ASM,$(<),$(@))
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMCFLAGS) $(ASMCFLAGS_$(*))

# Same as: as {--64,--32} a.S -o a.o
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	$(call log_tgt_obj,CC S,$(<),$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${TARGETS_CPP}: %:
	$(call log_tgt_exe,LD CXX,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
${TARGETS_ASM}: %:
	$(call log_tgt_exe,LD ASM,$(<),$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))
