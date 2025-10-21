target-y :=
target-y += abort
target-y += atof
target-y += mkdtemp mktemp mkstemp mkostemp
target-y += env environ setenv getenv clearenv putenv unsetenv
target-y += rand random random-dev srand srandom
target-y += bsearch
target-y += qsort
target-y += getloadavg
target-y += atexit
target-y += system
target-y += posix_memalign aligned_alloc
target-y += valloc
target-y += unlockpt
target-y += strtod strtof strtol strtold strtoul
target-y += setkey
target-y += rpmatch
target-y += ptsname
target-y += grantpt getpt
target-y += on_exit
target-y += l64a
target-y += initstate
target-y += getsubopt
target-y += ecvt fcvt gcvt
target-y += _Exit
target-y += open_pty_pair
target-y += div
target-y += demo-qsort-bsearch

CFLAGS :=

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
