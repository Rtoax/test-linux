#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/bpf.h>
#include <linux/btf.h>
#include <linux/btf_ids.h>
#include <linux/fs_struct.h>

/**
 * ref: https://eunomia.dev/tutorials/43-kfuncs/
 * lkml: https://lore.kernel.org/lkml/tencent_97F8B56B340F51DB604B482FEBF012460505@qq.com/
 * rtoax: https://github.com/Rtoax/linux/tree/p056-bpf_task_cwd
 */

__bpf_kfunc int bpf_task_cwd_from_pid(s32 pid, char *buf, u32 buf_len);

/* Begin kfunc definitions */
__bpf_kfunc_start_defs();

/**
 * bpf_task_cwd_from_pid - Get a task's absolute pathname of the current
 * working directory from its pid.
 * @pid: The pid of the task being looked up.
 * @buf: The array pointed to by buf.
 * @buf_len: buf length.
 */
__bpf_kfunc int bpf_task_cwd_from_pid(s32 pid, char *buf, u32 buf_len)
{
	struct path pwd;
	char kpath[256], *path;
	struct task_struct *task;

	if (!buf || buf_len == 0)
		return -EINVAL;

	rcu_read_lock();
	task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (!task) {
		rcu_read_unlock();
		return -ESRCH;
	}
	task_lock(task);
	if (!task->fs) {
		task_unlock(task);
		return -ENOENT;
	}
	get_fs_pwd(task->fs, &pwd);
	task_unlock(task);
	rcu_read_unlock();

	path = d_path(&pwd, kpath, sizeof(kpath));
	path_put(&pwd);
	if (IS_ERR(path))
		return PTR_ERR(path);

	strncpy(buf, path, buf_len);
	return 0;
}

/* End kfunc definitions */
__bpf_kfunc_end_defs();

/* Define the BTF kfuncs ID set */
BTF_KFUNCS_START(bpf_kfunc_example_ids_set)
BTF_ID_FLAGS(func, bpf_task_cwd_from_pid)
BTF_KFUNCS_END(bpf_kfunc_example_ids_set)

/* Register the kfunc ID set */
static const struct btf_kfunc_id_set bpf_kfunc_example_set = {
	.owner = THIS_MODULE,
	.set = &bpf_kfunc_example_ids_set,
};

/* Function executed when the module is loaded */
static int __init hello_init(void)
{
	int ret = 0;

	printk(KERN_INFO "Hello, world!\n");
	/* Register the BTF kfunc ID set for BPF_PROG_TYPE_KPROBE */
	ret = register_btf_kfunc_id_set(BPF_PROG_TYPE_KPROBE, &bpf_kfunc_example_set);
	ret = ret ?: register_btf_kfunc_id_set(BPF_PROG_TYPE_TRACEPOINT, &bpf_kfunc_example_set);
	if (ret) {
		pr_err("bpf_kfunc_example: Failed to register BTF kfunc ID set\n");
		return ret;
	}
	printk(KERN_INFO "bpf_kfunc_example: Module loaded successfully\n");
	return 0;
}

/* Function executed when the module is removed */
static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye, world!\n");
}

/* Macros to define the module’s init and exit points */
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rong Tao");
MODULE_DESCRIPTION("A simple module");
MODULE_VERSION("1.0");
