ARCH := $(shell uname -m)

targets-prep :=
LIBS :=

ifeq (${ARCH},x86_64)
  targets-prep += hello
  targets-prep += basic-vm
  targets-prep += load-payload01
  targets-prep += load-payload02
  targets-prep += cpuid
  targets-prep += assemly-compiling
  targets-prep += ia32e-paging
  targets-prep += protected-mode-with-paging
  targets-prep += exceptions
else ifeq (${ARCH},aarch64)
endif

CC := gcc
AS := as
NASM := nasm
OBJCOPY := objcopy

CFLAGS :=

LIBS += common.o

include ../../template/main.mk

hello: hello.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)
	${Q}$(AS) hello.asm -o hello.o
	${Q}$(OBJCOPY) -O binary hello.o hello.bin

basic-vm: basic-vm.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

load-payload01: load-payload01.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(NASM) load-payload01-program.asm -o load-payload01-program.bin
	${Q}$(NASM) -felf64 -o load-payload01-payload.o load-payload01-payload.asm
	${Q}$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<) $(LIBS)

load-payload02: load-payload02.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(NASM) load-payload02-program.asm -o load-payload02-program.bin
	${Q}$(CC) $(CFLAGS) -o $(@) load-payload01-payload.o $(<) $(LIBS)

cpuid: cpuid.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(NASM) cpuid-program.asm -o cpuid-program.bin
	${Q}$(NASM) -felf64 -o cpuid-payload.o cpuid-payload.asm
	${Q}$(CC) $(CFLAGS) -o $(@) cpuid-payload.o $(<) $(LIBS)

assemly-compiling:
	$(call log_tgt_exe,NASM,$(<),$(@))
	${Q}$(NASM) a16.asm -o a16.bin
	${Q}$(NASM) a32.asm -o a32.bin
	${Q}$(NASM) -O0 a64.asm -o a64.bin

ia32e-paging: ia32e-paging.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(NASM) -O0 ia32e-paging-a.asm -o ia32e-paging-a.bin
	${Q}$(NASM) -O0 ia32e-paging-b.asm -o ia32e-paging-b.bin
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

protected-mode-with-paging: protected-mode-with-paging.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(NASM) protected-mode-with-paging-a.asm -o protected-mode-with-paging-a.bin
	${Q}$(NASM) protected-mode-with-paging-b.asm -o protected-mode-with-paging-b.bin
	${Q}$(NASM) protected-mode-with-paging-c.asm -o protected-mode-with-paging-c.bin
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)

exceptions: exceptions.c common.o
	$(call log_tgt_exe,LD,$(<),$(@))
	${Q}$(NASM) exceptions-a.asm -o exceptions-a.bin
	${Q}$(NASM) exceptions-handler.asm -o exceptions-handler.bin
	${Q}$(CC) $(CFLAGS) -o $(@) $(<) $(LIBS)
