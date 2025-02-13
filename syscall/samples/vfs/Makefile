SHELL = bash
include ../../../tlbuild.mk



TARGETS := statfs
TARGETS += fstatfs

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -I../../../libs/

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
statfs: statfs.o proc.o
fstatfs: fstatfs.o

proc.o: ../../../libs/proc.o
	$(info We are in $(shell pwd))
	mv $(<) $(@)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
