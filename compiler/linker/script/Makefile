# SPDX-License-Identifier: GPL-3.0
target-asm-y :=
target-y := main-c
target-libso-y := libhello.so
target-prep-y := default.lds

ifeq ($(shell uname -m),x86_64)
  target-asm-y += hello-as
endif

# ld --verbose argument can print linker script
LDFLAGS := -Wl,--script=default.lds
ASMLDFLAGS_hello-as := --script hello-as.ld

LDFLAGS_SO_libhello.so := -Wl,--version-script=libhello.map

ifdef PIE
  LDS_PIE := PIE
endif

include ../../../template/main.mk

libhello.so: foo.so.o bar.so.o
foo.o: foo.h bar.h
bar.o: foo.h bar.h
main-c.o: foo.h bar.h
main-c: main-c.o foo.o bar.o
hello-as: hello-as.asm.o

default.lds:
	$(call log_tgt_exe,LDS,,$(@))
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}
