# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include glibc.mk
include ../scripts/logos.mk

sub-dir := arpa
sub-dir += alloca
sub-dir += byteswap
sub-dir += crypt
sub-dir += complex
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
sub-dir += ftw
sub-dir += fstab
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
sub-dir += netdb
sub-dir += net
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
sub-dir += syslog
sub-dir += sysinfo
sub-dir += sysmacros
sub-dir += termios
sub-dir += time
sub-dir += times
sub-dir += timex
sub-dir += ucontext
sub-dir += utmp
sub-dir += unistd
sub-dir += wctype
sub-dir += wordexp

MAKE_SUB_ARGS :=

TARGETS := environ
TARGETS += gnu_get_libc_version
TARGETS += lib-names
TARGETS += ftm _GNU_SOURCE _XOPEN_SOURCE

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

CC = gcc

CFLAGS :=
CFLAGS += -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  MAKE_SUB_ARGS += M32=1
  $(info Compile 32bit ELF)
endif

ifdef PIE
  CFLAGS += -pie -fPIE
  LDFLAGS += -pie -fPIE
  MAKE_SUB_ARGS += PIE=1
endif

ifdef NOPIE
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@$(call tl_ascii_logo_gnu)
	@echo -e " \033[1;33m Done \033[m"

gnu_get_libc_version: gnu_get_libc_version.o
environ: environ.o
lib-names: lib-names.o
ftm: ftm.o
_GNU_SOURCE: _GNU_SOURCE.o
_XOPEN_SOURCE: _XOPEN_SOURCE.o

CFLAGS__GNU_SOURCE := -D_GNU_SOURCE=1
CFLAGS__XOPEN_SOURCE := -D_XOPEN_SOURCE=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.out

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=) ${MAKE_SUB_ARGS}
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
