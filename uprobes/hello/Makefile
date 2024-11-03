SHELL = bash

TARGETS :=
TARGETS += hello
TARGETS += hello-pie

CC = gcc

CFLAGS := -Werror -Wall -O0

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie
CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o
hello-pie: hello-pie.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
