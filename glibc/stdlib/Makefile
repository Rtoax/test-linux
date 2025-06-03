TARGETS :=
TARGETS += abort
TARGETS += atof
TARGETS += mkdtemp mktemp mkstemp mkostemp
TARGETS += env environ setenv getenv clearenv putenv unsetenv
TARGETS += rand random random-dev srand srandom
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

CFLAGS := -Werror -Wall

CFLAGS_unlockpt := -D_XOPEN_SOURCE
# TODO
CFLAGS_unlockpt += -Wno-implicit-function-declaration

CFLAGS_srand := -DSRAND=1
CFLAGS_srandom := -DSRANDOM=1
CFLAGS_aligned_alloc := -DALIGNED_ALLOC=1
CFLAGS_valloc := -DVALLOC=1

include ../../template/main.mk

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
environ: environ.o
setenv: setenv.o
getenv: getenv.o
putenv: putenv.o
unsetenv: unsetenv.o
clearenv: clearenv.o
rand: rand.o
random: random.o
random-dev: random-dev.o
srand: srand.o
srandom: srandom.o
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
