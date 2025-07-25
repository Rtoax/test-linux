targets :=
targets += time
targets += alarm
targets += stime
targets += clock_getres
targets += clock_gettime clock_gettime-CLOCK_BOOTTIME
targets += clock_nanosleep
targets += nanosleep
targets += timeval
targets += getitimer setitimer setitimer-1
targets += gettimeofday settimeofday

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
