// SPDX-License-Identifier: GPL-2.0
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>

static struct proc_dir_entry *cmdline1 = NULL;

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_puts(m, "test cmdline");
	seq_putc(m, '\n');
	return 0;
}

static int __init cmdline_init(void)
{
	cmdline1 = proc_create_single("cmdline1", 0, NULL, cmdline_proc_show);
	return 0;
}

static void __exit cmdline_exit(void)
{
	proc_remove(cmdline1);
}

module_init(cmdline_init);
module_exit(cmdline_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("/proc/cmdline1");
