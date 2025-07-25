# SPDX-License-Identifier: GPL-3.0
targets :=
targets += time
targets += asctime asctime_r
targets += localtime
targets += clock
targets += clock_getcpuclockid
targets += difftime
targets += strftime
targets += strptime
targets += ctime
targets += getdate
targets += timelocal
targets += timegm
targets += gmtime
targets += mktime

targets += timer_create
targets += timer-demo

targets += iso8601
targets += timeval
targets += show_systime
targets += process-runtime

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
