// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

int sys_init_module(void *module_image, unsigned long len,
		    const char *param_values);
int sys_finit_module(int fd, const char *param_values, int flags);
int sys_delete_module(const char *name, unsigned int flags);
