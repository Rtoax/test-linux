TARGETS :=
TARGETS += mtrace

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lmcheck

LDFLAGS := $(CFLAGS)

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

mtrace: mtrace.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
