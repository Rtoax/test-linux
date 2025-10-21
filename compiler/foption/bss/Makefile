CC := gcc
include ../../compiler.mk

target-y :=
# Default
target-y += fzero-initialized-in-bss
target-y += fno-zero-initialized-in-bss

CFLAGS :=
CFLAGS += -Wno-error=unused-variable

CFLAGS_fzero-initialized-in-bss := -fzero-initialized-in-bss
CFLAGS_fno-zero-initialized-in-bss := -fno-zero-initialized-in-bss

include ../../../template/main.mk

fzero-initialized-in-bss: fzero-initialized-in-bss.o
fno-zero-initialized-in-bss: fno-zero-initialized-in-bss.o
