#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <errno.h>

#include "mod_helpers.h"


int sys_delete_module(const char *name, unsigned int flags)
{
	return syscall(SYS_delete_module, name, flags);
}
