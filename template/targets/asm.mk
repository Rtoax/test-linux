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
# - %.S.o
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

# Compile assembly code with AS
# Note: or we could use CC directly
# $1: asm source code extend, like: s, S
define obj_s
$${OUTPUT}%.${1}.o: %.${1} | $${OUTPUT}
	$$(call log_obj,AS ${1},$$(@))
	$${Q}$${AS} -o $$(@) $$(<) $$(ASFLAGS) $$(ASFLAGS_$$(*))
endef
$(eval $(call obj_s,s))
$(eval $(call obj_s,S))

# Default _start() entry and link libc
${target-as-y}: %:
	$(call log_tgt,LD S,$(@))
	${Q}$(LD) -lc -o $(@) $(^) $(ASLDFLAGS) $(ASLDFLAGS_$(*))

$(foreach t, ${target-asm-y} ${target-asm-std-y}, \
  $(if $(shell test -f ${t}.asm && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.asm.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
)

$(foreach t, ${target-as-y}, \
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
)

endif
