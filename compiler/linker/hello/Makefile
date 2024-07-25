SHELL = bash

LD = ld
NASM = $(shell which nasm 2>/dev/null)

TARGETS :=
ifeq ($(shell uname -m),x86_64)
  ifneq ($(NASM),)
    TARGETS += a.out hello.out
  endif
endif

all: ${TARGETS}

hello.o: hello.asm
	$(NASM) hello.asm -felf64

a.out: hello.o
	$(LD) $(<) -o $(@)

hello.out:
	$(LD) -T hello.ld -o $(@)
	@objdump -D hello.out | grep -e "\.text" -e "\.data" -A 2 | sed 's/^/[objdump] /g'

clean:
	@echo "CLEAN"
	@rm -f *.o *.out
