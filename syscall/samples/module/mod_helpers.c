// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <errno.h>
#include <linux/version.h>

#include "mod_helpers.h"

/* see init_module(2) */
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 4, 0)
int init_module(const char *name, struct module *image);
# error "Not support linux <= v2.4"
#endif

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
