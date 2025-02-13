SHELL = bash
include ../../tlbuild.mk


TARGETS :=
TARGETS += daemon
TARGETS += eaccess
TARGETS += execl
TARGETS += execle
TARGETS += execlp
TARGETS += execv
TARGETS += execve-fork
TARGETS += execve
TARGETS += execvp-fork
TARGETS += execvp-timedrun
TARGETS += execvp
TARGETS += getcwd
TARGETS += getpagesize
TARGETS += ttyname ttyname_r
TARGETS += lseek-huge
TARGETS += getdents64
TARGETS += ualarm
TARGETS += tcgetpgrp tcsetpgrp
TARGETS += execve-spawn
TARGETS += pathconf
TARGETS += cuserid
TARGETS += lockf lockf-nolock
TARGETS += isatty
TARGETS += getwd
TARGETS += getusershell
TARGETS += getpass
TARGETS += getdtablesize
TARGETS += get_current_dir_name
TARGETS += fexecve
TARGETS += getopt
TARGETS += _exit
TARGETS += gethostid


CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lrt

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
daemon: daemon.o
eaccess: eaccess.o
execl: execl.o
execle: execle.o
execlp: execlp.o
execv: execv.o
execve-fork: execve-fork.o
execve: execve.o
execvp-fork: execvp-fork.o
execvp-timedrun: execvp-timedrun.o
execvp: execvp.o
execve-spawn: execve-spawn.o
getcwd: getcwd.o
getpagesize: getpagesize.o
ttyname: ttyname.o
ttyname_r: ttyname_r.o
lseek-huge: lseek-huge.o
getdents64: getdents64.o
ualarm: ualarm.o
tcgetpgrp: tcgetpgrp.o
tcsetpgrp: tcsetpgrp.o
pathconf: pathconf.o
cuserid: cuserid.o
lockf: lockf.o
lockf-nolock: lockf-nolock.o
isatty: isatty.o
getwd: getwd.o
getusershell: getusershell.o
getpass: getpass.o
getdtablesize: getdtablesize.o
get_current_dir_name: get_current_dir_name.o
fexecve: fexecve.o
getopt: getopt.o
_exit: _exit.o
gethostid: gethostid.o

CFLAGS_getwd := -Wno-error=deprecated-declarations
CFLAGS_getwd += -Wno-deprecated-declarations

CFLAGS_lockf-nolock := -DNO_LOCK=1

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
	${Q}rm -rf tmpd-* tmp-*
