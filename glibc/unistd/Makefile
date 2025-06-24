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

CFLAGS :=
CFLAGS += -lrt

CFLAGS_getwd := -Wno-error=deprecated-declarations
CFLAGS_getwd += -Wno-deprecated-declarations

CFLAGS_lockf-nolock := -DNO_LOCK=1

include ../../template/main.mk

unistd_helpers.o: unistd_helpers.h

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
execvp: execvp.o unistd_helpers.o
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
