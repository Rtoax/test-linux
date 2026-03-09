# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_EXE_MK
_TARGET_EXE_MK = 1

CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm

include cflags.mk

${OUTPUT}%.o: %.c | ${OUTPUT}
	$(call log_obj,CC,$(@))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.E.c: %.c | ${OUTPUT}
	$(call log_obj,CC E,$(@))
	${Q}$(CC) -E -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	$(call log_obj,CC S,$(@))
	${Q}$(CC) -S -o $(@) $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	$(call log_obj,CXX,$(@))
	${Q}$(CXX) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	$(call log_obj,CXX S,$(@))
	${Q}$(CXX) -S -o $(@) $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

# Better define OUTPUT, to fix make: Circular dependency
${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_obj,ASM,$(@))
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMCFLAGS) $(ASMCFLAGS_$(*))

${OUTPUT}%.as.o: %.asm | ${OUTPUT}
	$(call log_obj,AS,$(@))
	${Q}${AS} -o $(@) $(<) $(ASCFLAGS) $(ASCFLAGS_$(*))

# Same as: as {--64,--32} a.S -o a.o
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	$(call log_obj,CC S,$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(target-y): %:
	$(call log_tgt,LD,$(@))
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${target-cpp-y}: %:
	$(call log_tgt,LD CXX,$(@))
	${Q}$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

# Same as: ld -m elf_i386 a.o -o a
${target-asm-y}: %:
	$(call log_tgt,LD ASM,$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))

$(foreach t, ${target-y}, $(eval ${t}: ${OUTPUT}${t}.o))
$(foreach t, ${target-cpp-y}, $(eval ${t}: ${OUTPUT}${t}.cpp.o))

$(foreach t, ${target-y}, \
  $(if $(shell test -f ${OUTPUT}${t}.o.d && echo yes), \
    $(if ${DEBUG}, $(info Found ${OUTPUT}${t}.o.d)) \
    $(eval include ${OUTPUT}${t}.o.d), \
    $(if ${DEBUG}, $(info Not found ${OUTPUT}${t}.o.d)) \
  ) \
)

$(foreach t, ${target-cpp-y}, \
  $(if $(shell test -f ${OUTPUT}${t}.cpp.o.d && echo yes), \
    $(if ${DEBUG}, $(info Found ${OUTPUT}${t}.cpp.o.d)) \
    $(eval include ${OUTPUT}${t}.cpp.o.d), \
    $(if ${DEBUG}, $(info Not found ${OUTPUT}${t}.cpp.o.d)) \
  ) \
)

endif
