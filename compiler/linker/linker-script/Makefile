# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

CC := gcc
LD := ld
NASM := $(shell which nasm 2>/dev/null)

TARGETS :=
TARGETS_ASM :=
TARGETS_LDS :=

LDS_PIE :=
AFLAGS :=
LDFLAGS :=

TARGETS_LDS += default.lds
TARGETS += main-c

ifeq ($(shell uname -m),x86_64)
  ifneq ($(NASM),)
    TARGETS_ASM += hello-as
  endif
endif

# ld --verbose argument can print linker script
LDFLAGS := -Wl,--script=default.lds
ALDFLAGS_hello-as := --script hello-as.ld

include ../../../elf/pie.mk

ifdef PIE
  LDS_PIE := PIE
endif

.PHONY: all
all: ${TARGETS_LDS} ${TARGETS_ASM} ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

foo.o: foo.h bar.h
bar.o: foo.h bar.h
main-c.o: foo.h bar.h
main-c: main-c.o foo.o bar.o
hello-as: hello-as.asm.o

default.lds:
	@echo -e "  LDS  generate \033[1;32m$(@)\033[m"
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}

%.asm.o: %.asm
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(NASM) $(<) -felf64 -o $(@) $(AFLAGS) $(AFLAGS_$(*))

${TARGETS_ASM}: %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(LD) -o $(@) $(ALDFLAGS) $(ALDFLAGS_$(*))

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS_ASM) $(TARGETS) $(TARGETS_LDS)\033[m"
	${Q}rm -f ${TARGETS_ASM} ${TARGETS} ${TARGETS_LDS} *.o
