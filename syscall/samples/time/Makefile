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

clock_getres-objs := time_helpers.o
clock_gettime-objs := time_helpers.o
clock_gettime-CLOCK_BOOTTIME-objs := time_helpers.o
clock_nanosleep-objs := time_helpers.o
nanosleep-objs := time_helpers.o

CFLAGS += -pthread
