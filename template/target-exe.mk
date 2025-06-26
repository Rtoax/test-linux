# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
CXX ?= g++
LD ?= ld
AS ?= as
NASM ?= nasm
CC_PFX := LD_LIBRARY_PATH=$(shell pwd)

${OUTPUT}%.o: %.c | ${OUTPUT}
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	@echo -e "  CC S \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${CC_PFX} $(CC) -S -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${CC_PFX} $(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	@echo -e "  CXX S  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${CC_PFX} $(CXX) -S -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	@echo -e "  ASM  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${NASM} -o $(@) -felf64 $(<) $(ASMCFLAGS) $(ASMCFLAGS_$(*))

# Same as: as {--64,--32} a.S -o a.o
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	@echo -e "  CC S  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${TARGETS_CPP}: %:
	@echo -e "  LD CXX   \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	${Q}${CC_PFX} $(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

${TARGETS_ASM}: %:
	@echo -e "  LD ASM   \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))
