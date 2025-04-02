#include <linux/init.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>

static int __init mymem_init(void)
{
	int slen, i;
	char *s;

	printk("mymem module is working..\n");

	slen = 1024;
	s = (char*)vmalloc(slen);

	for (i = 0; i < slen - 1; i++) {
		s[i] = 'A';
	}
	s[i] = '\n';

	printk(KERN_INFO "s = %s\n", s);
	/**
	 * undefined in module
	 */
	//printk_safe_flush();

	vfree(s);

	return 0;
}

static void __exit mymem_exit(void)
{
	printk("mymem module is leaving..\n");
}

module_init(mymem_init);
module_exit(mymem_exit);
MODULE_LICENSE("GPL");
