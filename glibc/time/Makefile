# SPDX-License-Identifier: GPL-3.0
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

CFLAGS :=
CFLAGS += -pthread -lrt

LDFLAGS := -pthread -lrt

include ../../template/main.mk

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
