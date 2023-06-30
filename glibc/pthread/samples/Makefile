
TARGETS += pthread_atfork
TARGETS += create_thread
TARGETS += dead_lock-1
TARGETS += dead_lock-2
TARGETS += pthread_attr_setstacksize
TARGETS += pthread_attr_setstack-1
TARGETS += pthread_attr_setstack-2
TARGETS += pthread_attr_setstack-3
TARGETS += pthread_attr_init 
TARGETS += pthread_barrier_init
TARGETS += pthread_cancel pthread_testcancel pthread_setcancelstate
TARGETS += pthread_create
TARGETS += pthread_create-deadline
TARGETS += pthread_cleanup_push
TARGETS += pthread_cleanup_push-deadlock
TARGETS += pthread_cleanup_push_defer_np
TARGETS += pthread_equal
TARGETS += pthread_exit
TARGETS += pthread_key_create pthread_setspecific
TARGETS += pthread_join-coredump
TARGETS += pthread_join pthread_tryjoin_np pthread_timedjoin_np
TARGETS += pthread_getname_np pthread_setname_np
TARGETS += pthread_self
TARGETS += pthread_spin_lock
TARGETS += pthread_spin-latency pthread_spin-latency-loop
TARGETS += pthread_setaffinity_np
TARGETS += pthread_once
TARGETS += pthread_yield
TARGETS += tls

ifeq ($(shell uname -m),x86_64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -pthread
CFLAGS += -I../../../
CFLAGS += -lm

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
pthread_barrier_init: pthread_barrier_init.o
pthread_cancel: pthread_cancel.o
pthread_testcancel: pthread_testcancel.o
pthread_setcancelstate: pthread_setcancelstate.o
pthread_cleanup_push: pthread_cleanup_push.o
pthread_cleanup_push-deadlock: pthread_cleanup_push-deadlock.o
pthread_cleanup_push_defer_np: pthread_cleanup_push_defer_np.o
pthread_create: pthread_create.o
pthread_create-deadline: pthread_create-deadline.o
pthread_equal: pthread_equal.o
pthread_exit: pthread_exit.o
pthread_key_create: pthread_key_create.o
pthread_join-coredump: pthread_join-coredump.o
pthread_join: pthread_join.o
pthread_tryjoin_np: pthread_tryjoin_np.o
pthread_timedjoin_np: pthread_timedjoin_np.o
pthread_getname_np: pthread_getname_np.o
pthread_setname_np: pthread_setname_np.o
pthread_self: pthread_self.o
pthread_setspecific: pthread_setspecific.o
pthread_setaffinity_np: pthread_setaffinity_np.o
pthread_spin_lock: pthread_spin_lock.o
pthread_spin-latency: pthread_spin-latency.o
pthread_spin-latency-loop: pthread_spin-latency-loop.o
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
