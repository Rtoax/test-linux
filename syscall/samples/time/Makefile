SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += alarm
TARGETS += stime
TARGETS += clock_getres
TARGETS += clock_gettime clock_gettime-CLOCK_BOOTTIME
TARGETS += clock_nanosleep
TARGETS += nanosleep
TARGETS += timeval
TARGETS += getitimer setitimer setitimer-1
TARGETS += gettimeofday settimeofday

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
alarm: alarm.o
clock_getres: clock_getres.o helpers.o
clock_gettime: clock_gettime.o helpers.o
clock_gettime-CLOCK_BOOTTIME: clock_gettime-CLOCK_BOOTTIME.o helpers.o
clock_nanosleep: clock_nanosleep.o helpers.o
stime: stime.o
nanosleep: nanosleep.o
timeval: timeval.o
getitimer: getitimer.o
setitimer: setitimer.o
setitimer-1: setitimer-1.o
gettimeofday: gettimeofday.o
settimeofday: settimeofday.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
