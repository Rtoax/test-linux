SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS := vsyscall-vma

all: ${TARGETS}
clean:
	rm -f ${TARGETS} *.elf
