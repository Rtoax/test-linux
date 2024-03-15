TARGETS :=
TARGETS += daemon
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

ifeq ($(shell uname -m),x86_64)
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
daemon: daemon.o
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

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
	@rm -rf tmpd-* tmp-*
