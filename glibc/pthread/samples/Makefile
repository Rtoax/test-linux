
TARGETS += pthread_atfork
TARGETS += create_thread
TARGETS += dead_lock-1
TARGETS += dead_lock-2
TARGETS += pthread_attr_setstacksize
TARGETS += pthread_attr_setstack-1
TARGETS += pthread_attr_setstack-2
TARGETS += pthread_attr_setstack-3
TARGETS += pthread_attr_init 
TARGETS += pthread_cancel pthread_testcancel pthread_setcancelstate
TARGETS += pthread_create
TARGETS += pthread_create-deadline
TARGETS += pthread_exit
TARGETS += pthread_key_create pthread_setspecific
TARGETS += pthread_join-coredump
TARGETS += pthread_join
TARGETS += pthread_getname_np pthread_setname_np
TARGETS += pthread_self
TARGETS += pthread_once
TARGETS += pthread_yield
TARGETS += tls

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -pthread
CFLAGS += -I../../../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
create_thread: create_thread.o
dead_lock-1: dead_lock-1.o
dead_lock-2: dead_lock-2.o
pthread_atfork: pthread_atfork.o
pthread_attr_setstacksize: pthread_attr_setstacksize.o
pthread_attr_setstack-1: pthread_attr_setstack-1.o
pthread_attr_setstack-2: pthread_attr_setstack-2.o
pthread_attr_setstack-3: pthread_attr_setstack-3.o
pthread_attr_init: pthread_attr_init.o
pthread_cancel: pthread_cancel.o
pthread_testcancel: pthread_testcancel.o
pthread_setcancelstate: pthread_setcancelstate.o
pthread_create: pthread_create.o
pthread_create-deadline: pthread_create-deadline.o
pthread_exit: pthread_exit.o
pthread_key_create: pthread_key_create.o
pthread_join-coredump: pthread_join-coredump.o
pthread_join: pthread_join.o
pthread_getname_np: pthread_getname_np.o
pthread_setname_np: pthread_setname_np.o
pthread_self: pthread_self.o
pthread_setspecific: pthread_setspecific.o
pthread_once: pthread_once.o
pthread_yield: pthread_yield.o
tls: tls.o

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
	@rm -f ${TARGETS} *.o *.d *.log
