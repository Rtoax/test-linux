TARGETS :=

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
TARGETS += cacheflush
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

cacheflush: cacheflush.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o

