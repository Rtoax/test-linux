# SPDX-License-Identifier: GPL-3.0
targets :=
targets-asm :=

targets += main-c
targets-prep := default.lds

ifeq ($(shell uname -m),x86_64)
  targets-asm += hello-as
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
	$(call log_tgt_exe,LDS,,$(@))
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}
