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
TARGETS += timeval_substract
TARGETS += show_systime
TARGETS += process-runtime

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -pthread -lrt

LDFLAGS := -pthread -lrt

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
asctime: asctime.o
asctime_r: asctime_r.o
ctime: ctime.o
difftime: difftime.o
getdate: getdate.o
localtime: localtime.o helpers.o
clock: clock.o
clock_getcpuclockid: clock_getcpuclockid.o
strftime: strftime.o
strptime: strptime.o helpers.o
timelocal: timelocal.o
time: time.o
timegm: timegm.o helpers.o
gmtime: gmtime.o helpers.o
mktime: mktime.o
timer_create: timer_create.o
timer-demo: timer-demo.o
timeval_substract: timeval_substract.o
show_systime: show_systime.o
process-runtime: process-runtime.o
iso8601: iso8601.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
