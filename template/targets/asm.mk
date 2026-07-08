# SPDX-License-Identifier: GPL-3.0
#
# Assembler Types
# | Command | Assembler Type | Grammar | Example      | Extension |
# | ------- | -------------- | ------- | ------------ | --------- |
# | as      | GNU            | AT&T    | mov %ax, %bx | .s        |
# | gcc     | GNU            | AT&T    | mov %ax, %bx | .S        |
# | nasm    | Netwide        | Intel   | mov bx, ax   | .asm      |
#
# Targets:
# - %.s.o
# - %.s.o.bin
# - %.S.o
# - %.asm.o (ASMFLAGS_NO_DEFAULT_ELF64=0)
# - %.asm.o.bin
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
OBJCOPY ?= objcopy

include cflags.mk

# More to see 'nasm -felf64 -y'
ifdef M32
  ASMFLAGS += -felf32
  ASMLDFLAGS += -m elf_i386
else
  ifndef ASMFLAGS_NO_DEFAULT_ELF64
    ASMFLAGS += -felf64
  endif
endif

# M32: -felf32
${OUTPUT}%.asm.o: %.asm | ${OUTPUT}
	$(call log_obj,${NASM},$(@))
	${Q}${NASM} -o $(@) $(<) $(ASMFLAGS) $(ASMFLAGS_$(*))

${OUTPUT}%.asm.o.bin: ${OUTPUT}%.asm.o
	$(call log_obj,${OBJCOPY} NASM BIN,$(@))
	${Q}${OBJCOPY} -O binary $(<) $(@)

# Same as: ld -m elf_i386 a.o -o a
${target-asm-y}: %:
	$(call log_tgt,${LD} ASM,$(@))
	${Q}$(LD) -o $(@) $(^) $(ASMLDFLAGS) $(ASMLDFLAGS_$(*))

$(target-asm-std-y): %:
	$(call log_tgt,${CC} ASM STD,$(@))
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

# .S files can be compiled directly with GCC because .S files can use GCC's
# preprocessing capabilities, while .s files will treat the preprocessor's '#'
# symbol as a comment and will not perform any processing.
${OUTPUT}%.S.o: %.S | ${OUTPUT}
	$(call log_obj,${CC} S,$(@))
	${Q}${CC} -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.s.o: %.s | ${OUTPUT}
	$(call log_obj,${AS},$(@))
	${Q}${AS} -o $(@) $(<) $(ASFLAGS) $(ASFLAGS_$(*))

${OUTPUT}%.s.o.bin: ${OUTPUT}%.s.o
	$(call log_obj,${OBJCOPY} BIN,$(@))
	${Q}${OBJCOPY} -O binary $(<) $(@)

# Default _start() entry and link libc
${target-as-y}: %:
	$(call log_tgt,${LD} S,$(@))
	${Q}$(LD) -lc -o $(@) $(^) $(ASLDFLAGS) $(ASLDFLAGS_$(*))

$(foreach t, ${target-asm-y} ${target-asm-std-y}, \
  $(eval ${t}-objs := $(call append_output_prefix,${${t}-objs})) \
  $(if ${DEBUG},$(info ${t}-objs = ${${t}-objs})) \
  $(if $(shell test -f ${t}.asm && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.asm.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
  $(if ${${t}-deps}, $(eval ${t}: ${${t}-deps})) \
)

$(foreach t, ${target-as-y}, \
  $(eval ${t}-objs := $(call append_output_prefix,${${t}-objs})) \
  $(if ${DEBUG},$(info ${t}-objs = ${${t}-objs})) \
  $(if $(shell test -f ${t}.S && test -f ${t}.s && echo yes), \
    $(error Not allow ${t}.S and ${t}.s exist at the same time) \
  ) \
  $(if $(shell test -f ${t}.s && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.s.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
  $(if $(shell test -f ${t}.S && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.S.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
  $(if ${${t}-deps}, $(eval ${t}: ${${t}-deps})) \
)

endif
