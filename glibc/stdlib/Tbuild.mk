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

CFLAGS_unlockpt := -D_XOPEN_SOURCE
# TODO
CFLAGS_unlockpt += -Wno-implicit-function-declaration

CFLAGS_srand := -DSRAND=1
CFLAGS_srandom := -DSRANDOM=1
CFLAGS_aligned_alloc := -DALIGNED_ALLOC=1
CFLAGS_valloc := -DVALLOC=1
