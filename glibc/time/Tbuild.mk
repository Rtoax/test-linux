# SPDX-License-Identifier: GPL-3.0
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

getdate-objs := time_helpers.o
localtime-objs := time_helpers.o
strptime-objs := time_helpers.o
timegm-objs := time_helpers.o
gmtime-objs := time_helpers.o

LDFLAGS := -pthread -lrt
