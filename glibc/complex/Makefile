TARGETS :=
TARGETS += _Complex_I _Complex __complex__

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wno-error=unused-variable
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

_Complex_I: _Complex_I.o
_Complex: _Complex.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
