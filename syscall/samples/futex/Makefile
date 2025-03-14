include ../../../tlbuild.mk



TARGETS := wait-wake
TARGETS += requeue
TARGETS += h2o
TARGETS += spin
TARGETS += latency

DEBUG := yes
CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../../
CFLAGS += -I../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

requeue: requeue.o
wait-wake: wait-wake.o
h2o: h2o.o
spin: spin.o
latency: latency.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
