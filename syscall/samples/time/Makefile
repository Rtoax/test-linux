target-y :=
target-y += time
target-y += alarm
target-y += stime
target-y += clock_getres
target-y += clock_gettime clock_gettime-CLOCK_BOOTTIME
target-y += clock_nanosleep
target-y += nanosleep
target-y += timeval
target-y += getitimer setitimer setitimer-1
target-y += gettimeofday settimeofday

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

time: time.o
alarm: alarm.o
clock_getres: clock_getres.o time_helpers.o
clock_gettime: clock_gettime.o time_helpers.o
clock_gettime-CLOCK_BOOTTIME: clock_gettime-CLOCK_BOOTTIME.o time_helpers.o
clock_nanosleep: clock_nanosleep.o time_helpers.o
stime: stime.o
nanosleep: nanosleep.o time_helpers.o
timeval: timeval.o
getitimer: getitimer.o
setitimer: setitimer.o
setitimer-1: setitimer-1.o
gettimeofday: gettimeofday.o
settimeofday: settimeofday.o
