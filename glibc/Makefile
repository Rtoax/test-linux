sub-dir := arpa
sub-dir += auxv
sub-dir += alloca
sub-dir += byteswap
sub-dir += crypt
sub-dir += complex
sub-dir += ctype
sub-dir += dirent
sub-dir += dlfcn
sub-dir += err
sub-dir += error
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
sub-dir += spawn
sub-dir += stat
sub-dir += stdarg
sub-dir += stdio
sub-dir += stdlib
sub-dir += string
sub-dir += strings
sub-dir += syslog
sub-dir += sysinfo
sub-dir += termios
sub-dir += time
sub-dir += ucontext
sub-dir += utmp
sub-dir += unistd
sub-dir += wctype
sub-dir += wordexp

TARGETS := environ
TARGETS += gnu_get_libc_version
TARGETS += lib-names
TARGETS += ftm _GNU_SOURCE _XOPEN_SOURCE

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
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
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d *.out

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	make -C $(@:.clean=) clean
