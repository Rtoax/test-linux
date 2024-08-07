SHELL = bash

CS_HDR_PLATFORM = /usr/include/capstone/platform.h

TARGETS :=
TARGETS += demo

ifneq ($(wildcard $(STDIO_HEADER)),)
  TARGETS :=
else
  $(warning "WARNING: You need to install capstone development")
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lcapstone

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

demo: demo.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o
