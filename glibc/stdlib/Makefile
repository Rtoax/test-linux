SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += abort
TARGETS += atof
TARGETS += mkdtemp mktemp mkstemp mkostemp
TARGETS += env setenv getenv clearenv putenv unsetenv
TARGETS += rand random random-dev srand
TARGETS += bsearch
TARGETS += qsort
TARGETS += getloadavg
TARGETS += atexit
TARGETS += system
TARGETS += posix_memalign aligned_alloc
TARGETS += valloc
TARGETS += unlockpt
TARGETS += strtod strtof strtol strtold strtoul
TARGETS += setkey
TARGETS += rpmatch
TARGETS += ptsname
TARGETS += grantpt getpt
TARGETS += on_exit
TARGETS += l64a
TARGETS += initstate
TARGETS += getsubopt
TARGETS += ecvt fcvt gcvt
TARGETS += _Exit
TARGETS += open_pty_pair
TARGETS += div
TARGETS += demo-qsort-bsearch

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g -ggdb

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
abort: abort.o
atof: atof.o
atexit: atexit.o
bsearch: bsearch.o
qsort: qsort.o
mkdtemp: mkdtemp.o
mktemp: mktemp.o
mkstemp: mkstemp.o
mkostemp: mkostemp.o
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
aligned_alloc: aligned_alloc.o
valloc: valloc.o
unlockpt: unlockpt.o
strtod: strtod.o
strtof: strtof.o
strtol: strtol.o
strtold: strtold.o
strtoul: strtoul.o
setkey: setkey.o
rpmatch: rpmatch.o
ptsname: ptsname.o
grantpt: grantpt.o
getpt: getpt.o
on_exit: on_exit.o
l64a: l64a.o
initstate: initstate.o
getsubopt: getsubopt.o
ecvt: ecvt.o
fcvt: fcvt.o
gcvt: gcvt.o
_Exit: _Exit.o
open_pty_pair: open_pty_pair.o
div: div.o
demo-qsort-bsearch: demo-qsort-bsearch.o

CFLAGS_unlockpt := -D_XOPEN_SOURCE
# TODO
CFLAGS_unlockpt += -Wno-implicit-function-declaration

CFLAGS_srand := -DSRAND=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.log
	${Q}rm -rf tmpd-* tmp-* *.dir
