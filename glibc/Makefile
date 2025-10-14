# SPDX-License-Identifier: GPL-3.0
include ../template/ansi.mk
include ../gnu/gnu.mk
include glibc.mk

sub-dir := alloca
sub-dir += arpa
sub-dir += byteswap
sub-dir += complex
sub-dir += crypt
sub-dir += ctype
sub-dir += dirent
sub-dir += dlfcn
sub-dir += err
sub-dir += errno
sub-dir += error
sub-dir += execinfo
sub-dir += fcntl
sub-dir += fenv
sub-dir += fnmatch
sub-dir += fstab
sub-dir += ftw
sub-dir += getopt
sub-dir += glob
sub-dir += grp
sub-dir += iconv
sub-dir += ld
sub-dir += libgen
sub-dir += link
sub-dir += locale
sub-dir += malloc
sub-dir += math
sub-dir += mntent
sub-dir += net
sub-dir += netdb
sub-dir += netinet
sub-dir += nl_types
sub-dir += obstack
sub-dir += printf
sub-dir += pthread
sub-dir += pwd
sub-dir += regex
sub-dir += scripts
sub-dir += search
sub-dir += semaphore
sub-dir += setjmp
sub-dir += shadow
sub-dir += signal
sub-dir += spawn
sub-dir += stat
sub-dir += stdarg
sub-dir += stdio
sub-dir += stdlib
sub-dir += string
sub-dir += strings
sub-dir += sys
sub-dir += sysinfo
sub-dir += syslog
sub-dir += sysmacros
sub-dir += termios
sub-dir += time
sub-dir += times
sub-dir += timex
sub-dir += ucontext
sub-dir += unistd
sub-dir += utmp
sub-dir += wctype
sub-dir += wordexp

targets := environ
targets += gnu_get_libc_version
targets += lib-names
targets += ftm _GNU_SOURCE _XOPEN_SOURCE
targets += __progname

CFLAGS := -pthread

CFLAGS__GNU_SOURCE := -D_GNU_SOURCE=1
CFLAGS__XOPEN_SOURCE := -D_XOPEN_SOURCE=1

targets-post := post

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
