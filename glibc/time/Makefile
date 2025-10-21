# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += time
target-y += asctime asctime_r
target-y += localtime
target-y += clock
target-y += clock_getcpuclockid
target-y += difftime
target-y += strftime
target-y += strptime
target-y += ctime
target-y += getdate
target-y += timelocal
target-y += timegm
target-y += gmtime
target-y += mktime

target-y += timer_create
target-y += timer-demo

target-y += iso8601
target-y += timeval
target-y += show_systime
target-y += process-runtime

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
