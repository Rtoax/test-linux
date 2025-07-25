CC := gcc
include ../../compiler.mk

targets :=
# Default
targets += fzero-initialized-in-bss
targets += fno-zero-initialized-in-bss

CFLAGS :=
CFLAGS += -Wno-error=unused-variable

CFLAGS_fzero-initialized-in-bss := -fzero-initialized-in-bss
CFLAGS_fno-zero-initialized-in-bss := -fno-zero-initialized-in-bss

include ../../../template/main.mk

fzero-initialized-in-bss: fzero-initialized-in-bss.o
fno-zero-initialized-in-bss: fno-zero-initialized-in-bss.o
