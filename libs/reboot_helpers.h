// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int sys_reboot(int magic, int magic2, int op, void *arg);

#ifdef __cplusplus
}
#endif
