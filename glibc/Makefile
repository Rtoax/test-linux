# SPDX-License-Identifier: GPL-3.0
include ../template/ansi.mk
include ../gnu/gnu.mk
include glibc.mk

subdir-y := alloca
subdir-y += arpa
subdir-y += byteswap
subdir-y += complex
subdir-y += crypt
subdir-y += ctype
subdir-y += dirent
subdir-y += dlfcn
subdir-y += err
subdir-y += errno
subdir-y += error
subdir-y += execinfo
subdir-y += fcntl
subdir-y += fenv
subdir-y += fnmatch
subdir-y += fstab
subdir-y += ftw
subdir-y += getopt
subdir-y += glob
subdir-y += grp
subdir-y += iconv
subdir-y += ld
subdir-y += libgen
subdir-y += link
subdir-y += locale
subdir-y += malloc
subdir-y += math
subdir-y += mntent
subdir-y += net
subdir-y += netdb
subdir-y += netinet
subdir-y += nl_types
subdir-y += obstack
subdir-y += printf
subdir-y += pthread
subdir-y += pwd
subdir-y += regex
subdir-y += scripts
subdir-y += search
subdir-y += semaphore
subdir-y += setjmp
subdir-y += shadow
subdir-y += signal
subdir-y += spawn
subdir-y += stat
subdir-y += stdarg
subdir-y += stdio
subdir-y += stdlib
subdir-y += string
subdir-y += strings
subdir-y += sys
subdir-y += sysinfo
subdir-y += syslog
subdir-y += sysmacros
subdir-y += termios
subdir-y += time
subdir-y += times
subdir-y += timex
subdir-y += ucontext
subdir-y += unistd
subdir-y += utmp
subdir-y += wctype
subdir-y += wordexp

target-y := environ
target-y += gnu_get_libc_version
target-y += lib-names
target-y += ftm _GNU_SOURCE _XOPEN_SOURCE
target-y += __progname

CFLAGS := -pthread

CFLAGS__GNU_SOURCE := -D_GNU_SOURCE=1
CFLAGS__XOPEN_SOURCE := -D_XOPEN_SOURCE=1

target-post-y := post

include ../template/main.mk

post:
	@$(call gnu_logo)

gnu_get_libc_version: gnu_get_libc_version.o
environ: environ.o
lib-names: lib-names.o
ftm: ftm.o
__progname: __progname.o
_GNU_SOURCE: _GNU_SOURCE.o
_XOPEN_SOURCE: _XOPEN_SOURCE.o
