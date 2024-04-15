TARGETS :=
TARGETS += mkdtemp mktemp mkstemp
TARGETS += env setenv getenv clearenv putenv unsetenv
TARGETS += rand random random-dev
TARGETS += bsearch
TARGETS += qsort
TARGETS += getloadavg
TARGETS += atexit
TARGETS += system

ifeq ($(shell uname -m),x86_64)
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
atexit: atexit.o
bsearch: bsearch.o
qsort: qsort.o
mkdtemp: mkdtemp.o
mktemp: mktemp.o
mkstemp: mkstemp.o
env: env.o
setenv: setenv.o
getenv: getenv.o
putenv: putenv.o
unsetenv: unsetenv.o
clearenv: clearenv.o
rand: rand.o
random: random.o
random-dev: random-dev.o
getloadavg: getloadavg.o
system: system.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./qsort b a c 2 1 3

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
	@rm -rf tmpd-* tmp-* *.dir
