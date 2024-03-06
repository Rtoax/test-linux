CC = gcc

TARGETS := mkfifo

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

mkfifo: mkfifo.o

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.tmp
