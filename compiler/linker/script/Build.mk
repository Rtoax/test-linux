# SPDX-License-Identifier: GPL-3.0
target-y := main
target-libso-y := libhello.so
prep-y := default.lds

target-asm-${IS_X86_64} += hello

# ld --verbose argument can print linker script
LDFLAGS := -Wl,--script=default.lds
ASMLDFLAGS_hello := --script hello.ld

LDFLAGS_SO_libhello.so := -Wl,--version-script=libhello.map

ifdef PIE
  LDS_PIE := PIE
endif

libhello.so-objs := foo.so.o bar.so.o
main-objs := foo.o bar.o
