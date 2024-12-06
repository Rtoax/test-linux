SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



TARGETS := pthread_none
TARGETS += pthread_orig
TARGETS += pthread_pthread

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I$(shell realpath ../../../)

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
pthread_none: pthread_none.o
pthread_orig: pthread_orig.o
pthread_pthread: pthread_pthread.o

CFLAGS_pthread_none := -DSPIN_NONE
CFLAGS_pthread_orig := -DSPIN_ORIG
CFLAGS_pthread_pthread := -DSPIN_PTHREAD

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
