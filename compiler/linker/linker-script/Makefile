# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS_ASM :=

TARGETS += main-c
TARGETS_PREP := default.lds

ifeq ($(shell uname -m),x86_64)
  TARGETS_ASM += hello-as
endif

# ld --verbose argument can print linker script
LDFLAGS := -Wl,--script=default.lds
ASMLDFLAGS_hello-as := --script hello-as.ld

include ../../../elf/pie.mk

ifdef PIE
  LDS_PIE := PIE
endif

include ../../../template/main.mk

foo.o: foo.h bar.h
bar.o: foo.h bar.h
main-c.o: foo.h bar.h
main-c: main-c.o foo.o bar.o
hello-as: hello-as.asm.o

default.lds:
	@echo -e "  LDS  generate \033[1;32m$(@)\033[m"
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}
