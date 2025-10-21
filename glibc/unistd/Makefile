target-y :=
target-y += daemon
target-y += eaccess
target-y += execl
target-y += execle
target-y += execlp
target-y += execv
target-y += execve-fork
target-y += execve
target-y += execvp-fork
target-y += execvp-timedrun
target-y += execvp
target-y += getcwd
target-y += getpagesize
target-y += ttyname ttyname_r
target-y += lseek-huge
target-y += getdents64
target-y += ualarm
target-y += tcgetpgrp tcsetpgrp
target-y += execve-spawn
target-y += pathconf
target-y += cuserid
target-y += lockf lockf-nolock
target-y += isatty
target-y += getwd
target-y += getusershell
target-y += getpass
target-y += getdtablesize
target-y += get_current_dir_name
target-y += fexecve
target-y += getopt
target-y += _exit
target-y += gethostid

LDFLAGS := -lrt

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
