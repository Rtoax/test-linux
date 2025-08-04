// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#ifdef __has_include
# if __has_include(<linux/mount.h>)
#  include <linux/mount.h>
# endif
#endif

int sys_fsopen(const char *fs_name, unsigned int flags);

int sys_fsmount(int fsfd, unsigned int flags, unsigned int ms_flags);

int sys_fsconfig(int fsfd, unsigned int cmd, const char *key, const void *val,
		 int aux);

int sys_move_mount(int from_dfd, const char *from_pathname, int to_dfd,
		   const char *to_pathname, unsigned int flags);

int get_free_dev_loop(void);

int bind_file_with_loop(const char *file, int *pffd, const char *dev_loop,
			int *plfd);
