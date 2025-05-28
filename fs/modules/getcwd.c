#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/path.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define BUF_SIZE 512

int get_task_cwd(pid_t pid, char *buf, size_t buflen)
{
	struct task_struct *task;
	struct path pwd_path;
	char *tmp;
	int ret = -ESRCH;

	rcu_read_lock();
	task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (!task) {
		rcu_read_unlock();
		return -ESRCH;
	}

	task_lock(task);
	if (!task->fs) {
		task_unlock(task);
		rcu_read_unlock();
		return -ENOENT;
	}
	get_fs_pwd(task->fs, &pwd_path);
	task_unlock(task);
	rcu_read_unlock();

	tmp = (char *)kmalloc(PATH_MAX, GFP_KERNEL);
	if (!tmp) {
		path_put(&pwd_path);
		return -ENOMEM;
	}

	tmp = d_path(&pwd_path, tmp, PATH_MAX);
	if (IS_ERR(tmp)) {
		ret = PTR_ERR(tmp);
		kfree(tmp);
		path_put(&pwd_path);
		return ret;
	}

	strlcpy(buf, tmp, buflen);

	kfree(tmp);
	path_put(&pwd_path);
	return 0;
}
EXPORT_SYMBOL(get_task_cwd);

static int __init mymod_init(void)
{
	char buf[BUF_SIZE];
	int ret = get_task_cwd(current->pid, buf, BUF_SIZE);
	if (ret == 0)
		printk(KERN_INFO "Current CWD: %s\n", buf);
	else
		printk(KERN_ERR "get_task_cwd failed: %d\n", ret);
	return -EINVAL;
}

module_init(mymod_init);
MODULE_LICENSE("GPL");
