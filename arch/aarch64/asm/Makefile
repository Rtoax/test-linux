
ifeq ($(shell uname -m),aarch64)
TARGETS := branch
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
branch: branch.o

%.o: %.S
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	as $(<) -o $(@)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	ld -o $(@) $(^) -lc -I /lib64/ld-linux-aarch64.so.1

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
