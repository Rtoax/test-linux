/**
 * File: uninterruptible.c
 * Author: ?
 * Modify by: Rong Tao
 *
 * TEST:
 * ---------------------------------------------------------
 * $ cat /sys/test/mytest/killable
 * $ kill -17 $(pidof cat) # SIGCHLD >> X
 * $ kill -9  $(pidof cat) # SIGKILL >> print
 * $ sudo sh -c "echo 3 > /sys/test/mytest/trigger" # killed
 *
 * 1: uninter
 * 2: inter
 * 3: killable
 *
 * Ref: https://www.cnblogs.com/hellokitty2/p/15415178.html
 */
#define pr_fmt(fmt) "mytest: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/wait.h>
#include <linux/sched.h>

struct mytest {
	int trigger_value;
	struct kobject *kobj;
	wait_queue_head_t uninter_wait;
	wait_queue_head_t inter_wait;
	wait_queue_head_t killable_wait;
};

static struct mytest test;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 14, 0)
# define Sfmt "%x"
# define STATE __state
#else
# define Sfmt "%lx"
# define STATE state
#endif 

/**
 * works ok
 */
ssize_t uninter_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	if (test.trigger_value != 1) {
		DECLARE_WAITQUEUE(wait, current);
		add_wait_queue(&test.uninter_wait, &wait);
		for (;;) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule();
			pr_info("uninter pid=%d %d was waken up! state=0x"Sfmt"\n",
				current->pid,
				((struct task_struct *)wait.private)->pid,
				((struct task_struct *)wait.private)->STATE);
			if (test.trigger_value == 1) {
				break;
			}
		}
		remove_wait_queue(&test.uninter_wait, &wait);
	}
	return sprintf(buf, "%d\n", test.trigger_value);
}
static struct kobj_attribute uninter_attr = {
	.attr    = {
		.name = __stringify(uninter),
		.mode = S_IRUGO,
	},
	.show    = uninter_show,
};


/**
 * works bad
 */
ssize_t inter_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	if (test.trigger_value != 2) {
		DECLARE_WAITQUEUE(wait, current);
		add_wait_queue(&test.inter_wait, &wait);
		for (;;) {
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
			pr_info("inter pid=%d %d was waken up! state=0x"Sfmt"\n",
				current->pid,
				((struct task_struct *)wait.private)->pid,
				((struct task_struct *)wait.private)->STATE);
			if (test.trigger_value == 2) { //process signal
				break;
			}
		}
		remove_wait_queue(&test.inter_wait, &wait);
	}
	return sprintf(buf, "%d\n", test.trigger_value);
}
static struct kobj_attribute inter_attr = {
	.attr    = {
		.name = __stringify(inter),
		.mode = S_IRUGO,
	},
	.show    = inter_show,
};

/**
 * works bad
 */
ssize_t killable_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	if (test.trigger_value != 3) {
		DECLARE_WAITQUEUE(wait, current);
		add_wait_queue(&test.killable_wait, &wait);
		for (;;) {
			set_current_state(TASK_KILLABLE);
			schedule();
			pr_info("killable pid=%d %d was waken up! state=0x"Sfmt"\n",
				current->pid,
				((struct task_struct *)wait.private)->pid,
				((struct task_struct *)wait.private)->STATE);
			if (test.trigger_value == 3) {
				break;
			}
		}
		remove_wait_queue(&test.killable_wait, &wait);
	}
	return sprintf(buf, "%d\n", test.trigger_value);
}
static struct kobj_attribute killable_attr = {
	.attr    = {
		.name = __stringify(killable),
		.mode = S_IRUGO,
	},
	.show    = killable_show,
};

ssize_t trigger_store(struct kobject *kobj, struct kobj_attribute *attr,
					  const char *buf, size_t count)
{
	int val;

	if (sscanf(buf, "%d", &val) != 1) {
		return -EINVAL;
	}
	test.trigger_value = val;

	switch(test.trigger_value) {
	case 1:
		wake_up_all(&test.uninter_wait);
		break;
	case 2:
		wake_up_all(&test.inter_wait);
		break;
	case 3:
		wake_up_all(&test.killable_wait);
		break;
	default:
		break;
	}

	return count;
}

ssize_t trigger_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", test.trigger_value);
}
static struct kobj_attribute trigger_attr = {
	.attr    = {
		.name = __stringify(trigger),
		.mode = 0644,
	},
	.show	= trigger_show,
	.store	= trigger_store,
};

static struct attribute *mytest_attrs[] = {
	&uninter_attr.attr,
	&inter_attr.attr,
	&killable_attr.attr,
	&trigger_attr.attr,
	NULL,
};

static struct attribute_group mytest_attr_group = {
	.name = "mytest",
	.attrs = mytest_attrs,
};


static int mytest_device_file_init(void)
{
	int ret = 0;

	test.kobj = kobject_create_and_add("test", NULL);
	if (!test.kobj) {
		pr_info("kobject_create_and_add failed!\n");
		return -ENOMEM;
	}

	ret = sysfs_create_group(test.kobj, &mytest_attr_group);
	if (ret) {
		pr_info("sysfs_create_group failed!\n");
		return ret;
	}

	return ret;
}

static int __init mytest_init(void)
{
	int ret;

	init_waitqueue_head(&test.uninter_wait);
	init_waitqueue_head(&test.inter_wait);
	init_waitqueue_head(&test.killable_wait);

	ret = mytest_device_file_init();

	pr_info("mytest_init probed! ret=%d\n", ret);

	return ret;
}

static void __exit mytest_exit(void)
{
	sysfs_remove_group(test.kobj, &mytest_attr_group);
	kobject_put(test.kobj);
	pr_info("mytest_exit removed\n");
}

module_init(mytest_init);
module_exit(mytest_exit);

MODULE_LICENSE("GPL");
