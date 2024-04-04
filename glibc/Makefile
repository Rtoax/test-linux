sub-dir := arpa
sub-dir += auxv
sub-dir += byteswap
sub-dir += crypt
sub-dir += dirent
sub-dir += dlfcn
sub-dir += errno
sub-dir += fenv
sub-dir += fstab
sub-dir += getopt
sub-dir += glob
sub-dir += grp
sub-dir += ld
sub-dir += libgen
sub-dir += link
sub-dir += malloc
sub-dir += math
sub-dir += pthread
sub-dir += pwd
sub-dir += regex
sub-dir += scripts
sub-dir += semaphore
sub-dir += spawn
sub-dir += stat
sub-dir += stdio
sub-dir += stdlib
sub-dir += string
sub-dir += syslog
sub-dir += sysinfo
sub-dir += termios
sub-dir += time
sub-dir += ucontext
sub-dir += unistd
sub-dir += wctype

TARGETS := environ
TARGETS += gnu_get_libc_version
TARGETS += lib-names

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
