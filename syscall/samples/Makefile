
TARGETS := fallocate
TARGETS += nr
TARGETS += openat2
TARGETS += pause
TARGETS += pidfd_open
TARGETS += setgid setegid
TARGETS += setuid seteuid
TARGETS += inotify_init

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: nr.h ${TARGETS}
	@echo
	make -C ioctl
	@echo -e " \033[1;33m Done \033[m"

nr.h:
	$(shell sh nr.sh)

# Add more object.o file
fallocate: fallocate.o
nr: nr.o
openat2: openat2.o
pause: pause.o
pidfd_open: pidfd_open.o
setgid: setgid.o
setegid: setegid.o
setuid: setuid.o
seteuid: seteuid.o
inotify_init: inotify_init.o


%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./fallocate.out

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	make -C ioctl clean
	@rm -f ${TARGETS} *.o *.d *.txt nr.h
