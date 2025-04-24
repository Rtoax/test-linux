#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <errno.h>

#include "mod_helpers.h"


int sys_init_module(void *module_image, unsigned long len,
		    const char *param_values)
{
	return syscall(SYS_init_module, module_image, len, param_values);
}

int sys_finit_module(int fd, const char *param_values, int flags)
{
	return syscall(SYS_finit_module, fd, param_values, flags);
}

int sys_delete_module(const char *name, unsigned int flags)
{
	return syscall(SYS_delete_module, name, flags);
}
