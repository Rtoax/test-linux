TARGETS :=
TARGETS += setjmp
TARGETS += sigsetjmp

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
setjmp: setjmp.o
sigsetjmp: sigsetjmp.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
