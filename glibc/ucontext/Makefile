include ../../tlbuild.mk



TARGETS := swapcontext
TARGETS += getcontext
TARGETS += ucontext_t
TARGETS += makecontext
TARGETS += demo1

ifeq ($(shell uname -m),x86_64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
swapcontext: swapcontext.o
getcontext: getcontext.o
ucontext_t: ucontext_t.o
makecontext: makecontext.o
demo1: demo1.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.log
	${Q}rm -rf tmpd-* tmp-*
