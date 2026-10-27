# SPDX-License-Identifier: GPL-3.0
include file.mk

# /usr/include/ dir
incdir-y += aio
incdir-y += aliases
incdir-y += alloca
incdir-y += argp
incdir-y += argz
incdir-y += arpa
incdir-y += assert
incdir-y += byteswap
incdir-y += complex
incdir-y += cpio
incdir-y += crypt
incdir-y += ctype
incdir-y += dirent
incdir-y += dlfcn
incdir-y += err
incdir-y += errno
incdir-y += error
incdir-y += execinfo
incdir-y += fcntl
incdir-y += features
incdir-y += fenv
incdir-y += float
incdir-y += fnmatch
incdir-$(call file_exists,/etc/fstab) += fstab
incdir-y += fts
incdir-y += ftw
incdir-y += getopt
incdir-y += glob
incdir-y += gnu
incdir-y += grp
incdir-y += iconv
incdir-y += ld
incdir-y += libgen
incdir-y += limits
incdir-y += link
incdir-y += locale
incdir-y += malloc
incdir-y += math
incdir-y += mntent
incdir-y += net
incdir-y += netdb
incdir-y += netinet
incdir-y += nl_types
incdir-y += obstack
incdir-y += printf
incdir-y += pthread
incdir-y += pwd
incdir-y += regex
incdir-y += scripts
incdir-y += search
incdir-y += semaphore
incdir-y += setjmp
incdir-y += shadow
incdir-y += signal
incdir-y += spawn
incdir-y += stat
incdir-y += stdarg
incdir-y += stdio
incdir-y += stdlib
incdir-y += string
incdir-y += strings
incdir-y += sys
incdir-y += sysinfo
incdir-y += syslog
incdir-y += termios
incdir-y += time
incdir-y += times
incdir-y += timex
incdir-y += ucontext
incdir-y += ulimit
incdir-y += unistd
incdir-y += utmp
incdir-y += utmpx
incdir-y += wctype
incdir-y += wordexp

subdir-y += ${incdir-y}

target-y += environ
target-y += ftm _GNU_SOURCE _XOPEN_SOURCE
target-y += __progname
target-y += __GLIBC_USE

prog-y += ${target-y}

CFLAGS__GNU_SOURCE := -D_GNU_SOURCE=1
CFLAGS__XOPEN_SOURCE := -D_XOPEN_SOURCE=1
CFLAGS___GLIBC_USE := -DTEST_MAIN=1

LDFLAGS := -pthread
