subdir-y += sysconf

target-y += daemon
target-y += eaccess
target-y += execl
target-y += execle
target-y += execlp
target-y += execv
target-y += execvp-fork
target-y += execvp-timedrun
target-y += execvp
target-y += getcwd
target-y += getpagesize
target-y += ttyname ttyname_r
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

execvp-objs := unistd_helpers.o

LDFLAGS := -lrt

CFLAGS_getwd := -Wno-error=deprecated-declarations
CFLAGS_getwd += -Wno-deprecated-declarations

CFLAGS_lockf-nolock := -DNO_LOCK=1

include main.mk
