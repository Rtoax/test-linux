TARGETS :=
TARGETS += mkdtemp mktemp mkstemp
TARGETS += env setenv getenv clearenv putenv unsetenv
TARGETS += rand random random-dev srand
TARGETS += bsearch
TARGETS += qsort
TARGETS += getloadavg
TARGETS += atexit
TARGETS += system
TARGETS += posix_memalign
TARGETS += valloc
TARGETS += unlockpt
TARGETS += strtod strtof strtol strtold strtoul
TARGETS += setkey
TARGETS += rpmatch

CC = gcc

CFLAGS := -Werror -Wall
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
srand: srand.o
getloadavg: getloadavg.o
system: system.o
posix_memalign: posix_memalign.o
valloc: valloc.o
unlockpt: unlockpt.o
strtod: strtod.o
strtof: strtof.o
strtol: strtol.o
strtold: strtold.o
strtoul: strtoul.o
setkey: setkey.o
rpmatch: rpmatch.o

CFLAGS_unlockpt := -D_XOPEN_SOURCE
# TODO
CFLAGS_unlockpt += -Wno-implicit-function-declaration

CFLAGS_srand := -DSRAND=1

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
	@rm -rf tmpd-* tmp-* *.dir
