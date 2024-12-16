SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


all:
	$(Q)gcc -fPIC -shared mcount-nop.c -o libmcount-nop.so
	$(Q)gcc main.c -pg -o main
	@echo -e " \033[1;33m Done \033[m"

run: main libmcount-nop.so
	$(Q)LD_PRELOAD=./libmcount-nop.so ./main

clean:
	@echo -e "  CLEAN"
	$(Q)rm -f main libmcount-nop.so
