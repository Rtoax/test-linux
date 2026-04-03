// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <errno.h>
#include <stdio.h>
#include <syscall.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "reboot_helpers.h"

int sys_reboot(int magic, int magic2, int op, void *arg)
{
	int err = syscall(__NR_reboot, magic, magic2, op, arg);
	if (err)
		errno = -err;
	return err;
}
