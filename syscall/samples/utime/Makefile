include ../../../tlbuild.mk


TARGETS :=
TARGETS += utime

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	touch a.txt
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
utime: utime.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.txt
