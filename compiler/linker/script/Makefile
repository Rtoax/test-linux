# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include arch.mk

target-y := main
target-libso-y := libhello.so
target-prep-y := default.lds

target-asm-${IS_X86_64} += hello

# ld --verbose argument can print linker script
LDFLAGS := -Wl,--script=default.lds
ASMLDFLAGS_hello := --script hello.ld

LDFLAGS_SO_libhello.so := -Wl,--version-script=libhello.map

ifdef PIE
  LDS_PIE := PIE
endif

libhello.so-objs := ${OUTPUT}foo.so.o ${OUTPUT}bar.so.o
main-objs := ${OUTPUT}foo.o ${OUTPUT}bar.o

include main.mk

hello: ${OUTPUT}hello.asm.o

default.lds:
	$(call log_tgt,LDS,$(@))
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}
