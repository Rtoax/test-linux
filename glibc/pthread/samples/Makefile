
TARGETS += pthread_attr_setstacksize
TARGETS += pthread_create
TARGETS += pthread_create-deadline
TARGETS += pthread_exit
TARGETS += pthread_join-coredump
TARGETS += pthread_join
TARGETS += pthread_getname_np
TARGETS += pthread_setname_np

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
pthread_attr_setstacksize: pthread_attr_setstacksize.o
pthread_create: pthread_create.o
pthread_create-deadline: pthread_create-deadline.o
pthread_exit: pthread_exit.o
pthread_join-coredump: pthread_join-coredump.o
pthread_join: pthread_join.o
pthread_getname_np: pthread_getname_np.o
pthread_setname_np: pthread_setname_np.o

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

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
