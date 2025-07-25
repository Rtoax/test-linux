targets :=
targets += daemon
targets += eaccess
targets += execl
targets += execle
targets += execlp
targets += execv
targets += execve-fork
targets += execve
targets += execvp-fork
targets += execvp-timedrun
targets += execvp
targets += getcwd
targets += getpagesize
targets += ttyname ttyname_r
targets += lseek-huge
targets += getdents64
targets += ualarm
targets += tcgetpgrp tcsetpgrp
targets += execve-spawn
targets += pathconf
targets += cuserid
targets += lockf lockf-nolock
targets += isatty
targets += getwd
targets += getusershell
targets += getpass
targets += getdtablesize
targets += get_current_dir_name
targets += fexecve
targets += getopt
targets += _exit
targets += gethostid

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
