# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

TARGETS :=
TARGETS += time
TARGETS += asctime asctime_r
TARGETS += localtime
TARGETS += clock
TARGETS += clock_getcpuclockid
TARGETS += difftime
TARGETS += strftime
TARGETS += strptime
TARGETS += ctime
TARGETS += getdate
TARGETS += timelocal
TARGETS += timegm
TARGETS += gmtime
TARGETS += mktime

TARGETS += timer_create
TARGETS += timer-demo

TARGETS += iso8601
TARGETS += timeval
TARGETS += show_systime
TARGETS += process-runtime

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -pthread -lrt

LDFLAGS := -pthread -lrt

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

time_helpers.o: time_helpers.h

asctime: asctime.o
asctime_r: asctime_r.o
ctime: ctime.o
difftime: difftime.o
getdate: getdate.o time_helpers.o
localtime: localtime.o time_helpers.o
clock: clock.o
clock_getcpuclockid: clock_getcpuclockid.o
strftime: strftime.o
strptime: strptime.o time_helpers.o
timelocal: timelocal.o
time: time.o
timegm: timegm.o time_helpers.o
gmtime: gmtime.o time_helpers.o
mktime: mktime.o
timer_create: timer_create.o
timer-demo: timer-demo.o
timeval: timeval.o
show_systime: show_systime.o
process-runtime: process-runtime.o
iso8601: iso8601.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d tfile.txt
