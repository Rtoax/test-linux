# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

CC := gcc
LD := ld
NASM := $(shell which nasm 2>/dev/null)

TARGETS_C :=
TARGETS_AS :=
TARGETS_LDS :=

LDS_PIE :=
AFLAGS :=
ALDFLAGS :=

TARGETS_LDS += default.lds
TARGETS_C += main-c

ifeq ($(shell uname -m),x86_64)
  ifneq ($(NASM),)
    TARGETS_AS += hello-as
  endif
endif

# ld --verbose argument can print linker script
LDFLAGS_C := -Wl,-Tdefault.lds

include ../../../elf/pie.mk

ifdef PIE
  LDS_PIE := PIE
endif

.PHONY: all
all: ${TARGETS_LDS} ${TARGETS_AS} ${TARGETS_C}
	@echo -e " \033[1;33m Done \033[m"

foo.o: foo.h bar.h
bar.o: foo.h bar.h
main-c.o: foo.h bar.h
main-c: main-c.o foo.o bar.o
hello-as: hello-as.o

default.lds:
	@echo -e "  LDS  generate \033[1;32m$(@)\033[m"
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}

%.o: %.asm
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(NASM) $(<) -felf64 -o $(@) $(AFLAGS) $(AFLAGS_$(*))

${TARGETS_AS}: %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(LD) -T $(@).ld -o $(@) $(ALDFLAGS) $(ALDFLAGS_$(*))

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_C): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_C) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS_AS) $(TARGETS_C) $(TARGETS_LDS)\033[m"
	${Q}rm -f ${TARGETS_AS} ${TARGETS_C} ${TARGETS_LDS} *.o
