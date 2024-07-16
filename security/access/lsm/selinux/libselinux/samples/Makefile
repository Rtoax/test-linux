SHELL = bash

TARGETS :=
TARGETS += getpidcon

CC = gcc
CFLAGS := -lselinux

build: $(TARGETS)

getpidcon: getpidcon.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(<)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
