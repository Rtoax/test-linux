
TARGETS :=
TARGETS += io_uring-cat
TARGETS += io_uring-cat-liburing
TARGETS += io_uring-multi-reqs
TARGETS += io_uring-web-server
TARGETS += ordinary-cat
TARGETS += link-cp
TARGETS += io_uring-test


DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -luring

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
io_uring-cat: io_uring-cat.o
io_uring-cat-liburing: io_uring-cat-liburing.o
io_uring-multi-reqs: io_uring-multi-reqs.o
io_uring-web-server: io_uring-web-server.o
ordinary-cat: ordinary-cat.o
link-cp: link-cp.o
io_uring-test: io_uring-test.o

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
	@rm -f ${TARGETS} *.o *.d
