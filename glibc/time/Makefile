TARGETS :=
TARGETS += asctime asctime_r
TARGETS += localtime localtime_r
TARGETS += clock
TARGETS += clock_getcpuclockid
TARGETS += strftime
TARGETS += strptime
TARGETS += ctime
TARGETS += timeval_substract

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
asctime: asctime.o
asctime_r: asctime_r.o
ctime: ctime.o
localtime: localtime.o
localtime_r: localtime_r.o
clock: clock.o
clock_getcpuclockid: clock_getcpuclockid.o
strftime: strftime.o
strptime: strptime.o
timeval_substract: timeval_substract.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
