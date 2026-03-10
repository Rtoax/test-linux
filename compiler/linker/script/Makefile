# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

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

libhello.so-objs := ${OUTPUT}foo.so.o ${OUTPUT}bar.so.o
main-c-objs := ${OUTPUT}foo.o ${OUTPUT}bar.o

include main.mk

hello-as: ${OUTPUT}hello-as.asm.o

default.lds:
	$(call log_tgt,LDS,$(@))
	${Q}LD=${LD} ./default.lds.sh ${LDS_PIE}
